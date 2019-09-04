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
struct stop_event_data {scalar_t__ restart; struct perf_event* event; } ;
struct perf_event {TYPE_1__* pmu; int /*<<< orphan*/  oncpu; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start ) (struct perf_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* stop ) (struct perf_event*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 scalar_t__ PERF_EVENT_STATE_ACTIVE ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ smp_processor_id () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  stub1 (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __perf_event_stop(void *info)
{
	struct stop_event_data *sd = info;
	struct perf_event *event = sd->event;

	/* if it's already INACTIVE, do nothing */
	if (READ_ONCE(event->state) != PERF_EVENT_STATE_ACTIVE)
		return 0;

	/* matches smp_wmb() in event_sched_in() */
	smp_rmb();

	/*
	 * There is a window with interrupts enabled before we get here,
	 * so we need to check again lest we try to stop another CPU's event.
	 */
	if (READ_ONCE(event->oncpu) != smp_processor_id())
		return -EAGAIN;

	event->pmu->stop(event, PERF_EF_UPDATE);

	/*
	 * May race with the actual stop (through perf_pmu_output_stop()),
	 * but it is only used for events with AUX ring buffer, and such
	 * events will refuse to restart because of rb::aux_mmap_count==0,
	 * see comments in perf_aux_output_begin().
	 *
	 * Since this is happening on an event-local CPU, no trace is lost
	 * while restarting.
	 */
	if (sd->restart)
		event->pmu->start(event, 0);

	return 0;
}