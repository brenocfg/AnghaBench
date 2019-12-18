#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {long tv_sec; int tv_usec; } ;
struct itimerval {TYPE_1__ it_value; } ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_4__ {int /*<<< orphan*/  fin_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  MemSet (struct itimerval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TimestampDifference (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*,int*) ; 
 TYPE_2__** active_timeouts ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  enable_alarm () ; 
 scalar_t__ num_active_timeouts ; 
 scalar_t__ setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
schedule_alarm(TimestampTz now)
{
	if (num_active_timeouts > 0)
	{
		struct itimerval timeval;
		long		secs;
		int			usecs;

		MemSet(&timeval, 0, sizeof(struct itimerval));

		/* Get the time remaining till the nearest pending timeout */
		TimestampDifference(now, active_timeouts[0]->fin_time,
							&secs, &usecs);

		/*
		 * It's possible that the difference is less than a microsecond;
		 * ensure we don't cancel, rather than set, the interrupt.
		 */
		if (secs == 0 && usecs == 0)
			usecs = 1;

		timeval.it_value.tv_sec = secs;
		timeval.it_value.tv_usec = usecs;

		/*
		 * We must enable the signal handler before calling setitimer(); if we
		 * did it in the other order, we'd have a race condition wherein the
		 * interrupt could occur before we can set alarm_enabled, so that the
		 * signal handler would fail to do anything.
		 *
		 * Because we didn't bother to reset the timer in disable_alarm(),
		 * it's possible that a previously-set interrupt will fire between
		 * enable_alarm() and setitimer().  This is safe, however.  There are
		 * two possible outcomes:
		 *
		 * 1. The signal handler finds nothing to do (because the nearest
		 * timeout event is still in the future).  It will re-set the timer
		 * and return.  Then we'll overwrite the timer value with a new one.
		 * This will mean that the timer fires a little later than we
		 * intended, but only by the amount of time it takes for the signal
		 * handler to do nothing useful, which shouldn't be much.
		 *
		 * 2. The signal handler executes and removes one or more timeout
		 * events.  When it returns, either the queue is now empty or the
		 * frontmost event is later than the one we looked at above.  So we'll
		 * overwrite the timer value with one that is too soon (plus or minus
		 * the signal handler's execution time), causing a useless interrupt
		 * to occur.  But the handler will then re-set the timer and
		 * everything will still work as expected.
		 *
		 * Since these cases are of very low probability (the window here
		 * being quite narrow), it's not worth adding cycles to the mainline
		 * code to prevent occasional wasted interrupts.
		 */
		enable_alarm();

		/* Set the alarm timer */
		if (setitimer(ITIMER_REAL, &timeval, NULL) != 0)
			elog(FATAL, "could not enable SIGALRM timer: %m");
	}
}