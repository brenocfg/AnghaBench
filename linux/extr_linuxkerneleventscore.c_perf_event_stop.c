#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stop_event_data {int restart; struct perf_event* event; } ;
struct perf_event {int /*<<< orphan*/  oncpu; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ PERF_EVENT_STATE_ACTIVE ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __perf_event_stop ; 
 int cpu_function_call (scalar_t__,int /*<<< orphan*/ ,struct stop_event_data*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static int perf_event_stop(struct perf_event *event, int restart)
{
	struct stop_event_data sd = {
		.event		= event,
		.restart	= restart,
	};
	int ret = 0;

	do {
		if (READ_ONCE(event->state) != PERF_EVENT_STATE_ACTIVE)
			return 0;

		/* matches smp_wmb() in event_sched_in() */
		smp_rmb();

		/*
		 * We only want to restart ACTIVE events, so if the event goes
		 * inactive here (event->oncpu==-1), there's nothing more to do;
		 * fall through with ret==-ENXIO.
		 */
		ret = cpu_function_call(READ_ONCE(event->oncpu),
					__perf_event_stop, &sd);
	} while (ret == -EAGAIN);

	return ret;
}