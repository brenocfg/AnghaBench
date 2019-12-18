#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_5__ {scalar_t__ pinned; scalar_t__ inherit; } ;
struct TYPE_4__ {scalar_t__ target; } ;
struct perf_event {int attach_state; scalar_t__ cpu; scalar_t__ oncpu; scalar_t__ shadow_ctx_time; int /*<<< orphan*/  count; TYPE_3__* pmu; TYPE_2__ attr; TYPE_1__ hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* read ) (struct perf_event*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int PERF_ATTACH_TASK ; 
 int /*<<< orphan*/  __perf_update_times (struct perf_event*,scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ current ; 
 scalar_t__ local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ perf_clock () ; 
 scalar_t__ smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 

int perf_event_read_local(struct perf_event *event, u64 *value,
			  u64 *enabled, u64 *running)
{
	unsigned long flags;
	int ret = 0;

	/*
	 * Disabling interrupts avoids all counter scheduling (context
	 * switches, timer based rotation and IPIs).
	 */
	local_irq_save(flags);

	/*
	 * It must not be an event with inherit set, we cannot read
	 * all child counters from atomic context.
	 */
	if (event->attr.inherit) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	/* If this is a per-task event, it must be for current */
	if ((event->attach_state & PERF_ATTACH_TASK) &&
	    event->hw.target != current) {
		ret = -EINVAL;
		goto out;
	}

	/* If this is a per-CPU event, it must be for this CPU */
	if (!(event->attach_state & PERF_ATTACH_TASK) &&
	    event->cpu != smp_processor_id()) {
		ret = -EINVAL;
		goto out;
	}

	/* If this is a pinned event it must be running on this CPU */
	if (event->attr.pinned && event->oncpu != smp_processor_id()) {
		ret = -EBUSY;
		goto out;
	}

	/*
	 * If the event is currently on this CPU, its either a per-task event,
	 * or local to this CPU. Furthermore it means its ACTIVE (otherwise
	 * oncpu == -1).
	 */
	if (event->oncpu == smp_processor_id())
		event->pmu->read(event);

	*value = local64_read(&event->count);
	if (enabled || running) {
		u64 now = event->shadow_ctx_time + perf_clock();
		u64 __enabled, __running;

		__perf_update_times(event, now, &__enabled, &__running);
		if (enabled)
			*enabled = __enabled;
		if (running)
			*running = __running;
	}
out:
	local_irq_restore(flags);

	return ret;
}