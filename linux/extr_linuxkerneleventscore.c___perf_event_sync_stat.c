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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  inherit_stat; } ;
struct perf_event {scalar_t__ state; int /*<<< orphan*/  total_time_running; int /*<<< orphan*/  total_time_enabled; int /*<<< orphan*/  count; TYPE_2__* pmu; TYPE_1__ attr; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* read ) (struct perf_event*) ;} ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_ACTIVE ; 
 int /*<<< orphan*/  local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local64_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_time (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __perf_event_sync_stat(struct perf_event *event,
				     struct perf_event *next_event)
{
	u64 value;

	if (!event->attr.inherit_stat)
		return;

	/*
	 * Update the event value, we cannot use perf_event_read()
	 * because we're in the middle of a context switch and have IRQs
	 * disabled, which upsets smp_call_function_single(), however
	 * we know the event must be on the current CPU, therefore we
	 * don't need to use it.
	 */
	if (event->state == PERF_EVENT_STATE_ACTIVE)
		event->pmu->read(event);

	perf_event_update_time(event);

	/*
	 * In order to keep per-task stats reliable we need to flip the event
	 * values when we flip the contexts.
	 */
	value = local64_read(&next_event->count);
	value = local64_xchg(&event->count, value);
	local64_set(&next_event->count, value);

	swap(event->total_time_enabled, next_event->total_time_enabled);
	swap(event->total_time_running, next_event->total_time_running);

	/*
	 * Since we swizzled the values, update the user visible data too.
	 */
	perf_event_update_userpage(event);
	perf_event_update_userpage(next_event);
}