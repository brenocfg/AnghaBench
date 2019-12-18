#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct itimerval {int dummy; } ;
struct TYPE_2__ {int active; int indicator; } ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int MAX_TIMEOUTS ; 
 int /*<<< orphan*/  MemSet (struct itimerval*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* all_timeouts ; 
 int /*<<< orphan*/  disable_alarm () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ num_active_timeouts ; 
 scalar_t__ setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 

void
disable_all_timeouts(bool keep_indicators)
{
	int			i;

	disable_alarm();

	/*
	 * Only bother to reset the timer if we think it's active.  We could just
	 * let the interrupt happen anyway, but it's probably a bit cheaper to do
	 * setitimer() than to let the useless interrupt happen.
	 */
	if (num_active_timeouts > 0)
	{
		struct itimerval timeval;

		MemSet(&timeval, 0, sizeof(struct itimerval));
		if (setitimer(ITIMER_REAL, &timeval, NULL) != 0)
			elog(FATAL, "could not disable SIGALRM timer: %m");
	}

	num_active_timeouts = 0;

	for (i = 0; i < MAX_TIMEOUTS; i++)
	{
		all_timeouts[i].active = false;
		if (!keep_indicators)
			all_timeouts[i].indicator = false;
	}
}