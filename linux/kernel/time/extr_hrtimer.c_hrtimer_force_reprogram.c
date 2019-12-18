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
struct hrtimer_cpu_base {scalar_t__ expires_next; scalar_t__ hang_detected; scalar_t__ softirq_expires_next; scalar_t__ softirq_activated; TYPE_1__* next_timer; } ;
typedef  scalar_t__ ktime_t ;
struct TYPE_2__ {scalar_t__ is_soft; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_ACTIVE_ALL ; 
 int /*<<< orphan*/  HRTIMER_ACTIVE_HARD ; 
 scalar_t__ __hrtimer_get_next_event (struct hrtimer_cpu_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hrtimer_hres_active (struct hrtimer_cpu_base*) ; 
 int /*<<< orphan*/  tick_program_event (scalar_t__,int) ; 

__attribute__((used)) static void
hrtimer_force_reprogram(struct hrtimer_cpu_base *cpu_base, int skip_equal)
{
	ktime_t expires_next;

	/*
	 * Find the current next expiration time.
	 */
	expires_next = __hrtimer_get_next_event(cpu_base, HRTIMER_ACTIVE_ALL);

	if (cpu_base->next_timer && cpu_base->next_timer->is_soft) {
		/*
		 * When the softirq is activated, hrtimer has to be
		 * programmed with the first hard hrtimer because soft
		 * timer interrupt could occur too late.
		 */
		if (cpu_base->softirq_activated)
			expires_next = __hrtimer_get_next_event(cpu_base,
								HRTIMER_ACTIVE_HARD);
		else
			cpu_base->softirq_expires_next = expires_next;
	}

	if (skip_equal && expires_next == cpu_base->expires_next)
		return;

	cpu_base->expires_next = expires_next;

	/*
	 * If hres is not active, hardware does not have to be
	 * reprogrammed yet.
	 *
	 * If a hang was detected in the last timer interrupt then we
	 * leave the hang delay active in the hardware. We want the
	 * system to make progress. That also prevents the following
	 * scenario:
	 * T1 expires 50ms from now
	 * T2 expires 5s from now
	 *
	 * T1 is removed, so this code is called and would reprogram
	 * the hardware to 5s from now. Any hrtimer_start after that
	 * will not reprogram the hardware due to hang_detected being
	 * set. So we'd effectivly block all timers until the T2 event
	 * fires.
	 */
	if (!__hrtimer_hres_active(cpu_base) || cpu_base->hang_detected)
		return;

	tick_program_event(cpu_base->expires_next, 1);
}