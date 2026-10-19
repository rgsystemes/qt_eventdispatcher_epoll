#ifndef EVENTDISPATCHER_EPOLL_H
#define EVENTDISPATCHER_EPOLL_H

#include <QtCore/QAbstractEventDispatcher>

// Qt 5+ requires C++11: use override directly, so that the checks can't silently disappear
#if QT_VERSION >= 0x050000
#	define EVENTDISPATCHER_EPOLL_OVERRIDE override
#else
#	define EVENTDISPATCHER_EPOLL_OVERRIDE
#endif

class EventDispatcherEPollPrivate;
class EventDispatcherLibEventConfig;

class EventDispatcherEPoll : public QAbstractEventDispatcher {
	Q_OBJECT
public:
	explicit EventDispatcherEPoll(QObject* parent = 0);
	virtual ~EventDispatcherEPoll(void);

	virtual bool processEvents(QEventLoop::ProcessEventsFlags flags) EVENTDISPATCHER_EPOLL_OVERRIDE;
#if QT_VERSION < 0x060000
	virtual bool hasPendingEvents(void) EVENTDISPATCHER_EPOLL_OVERRIDE;
#endif

	virtual void registerSocketNotifier(QSocketNotifier* notifier) EVENTDISPATCHER_EPOLL_OVERRIDE;
	virtual void unregisterSocketNotifier(QSocketNotifier* notifier) EVENTDISPATCHER_EPOLL_OVERRIDE;

#if QT_VERSION >= 0x060000
	// Don't hide the base class overloads (e.g. the Qt::TimerId ones since Qt 6.8)
	using QAbstractEventDispatcher::registerTimer;
	using QAbstractEventDispatcher::unregisterTimer;
	using QAbstractEventDispatcher::remainingTime;
#endif

	virtual void registerTimer(
		int timerId,
#if QT_VERSION >= 0x060000
		qint64 interval,
#else
		int interval,
#endif
#if QT_VERSION >= 0x050000
		Qt::TimerType timerType,
#endif
		QObject* object
	) EVENTDISPATCHER_EPOLL_OVERRIDE;

	virtual bool unregisterTimer(int timerId) EVENTDISPATCHER_EPOLL_OVERRIDE;
	virtual bool unregisterTimers(QObject* object) EVENTDISPATCHER_EPOLL_OVERRIDE;
	virtual QList<QAbstractEventDispatcher::TimerInfo> registeredTimers(QObject* object) const EVENTDISPATCHER_EPOLL_OVERRIDE;
#if QT_VERSION >= 0x050000
	virtual int remainingTime(int timerId) EVENTDISPATCHER_EPOLL_OVERRIDE;
#endif

	virtual void wakeUp(void) EVENTDISPATCHER_EPOLL_OVERRIDE;
	virtual void interrupt(void) EVENTDISPATCHER_EPOLL_OVERRIDE;
#if QT_VERSION < 0x060000
	virtual void flush(void) EVENTDISPATCHER_EPOLL_OVERRIDE;
#endif

private:
	Q_DISABLE_COPY(EventDispatcherEPoll)
	Q_DECLARE_PRIVATE(EventDispatcherEPoll)
#if QT_VERSION >= 0x040600
	QScopedPointer<EventDispatcherEPollPrivate> d_ptr;
#else
	EventDispatcherEPollPrivate* d_ptr;
#endif
};

#undef EVENTDISPATCHER_EPOLL_OVERRIDE

#endif // EVENTDISPATCHER_EPOLL_H
