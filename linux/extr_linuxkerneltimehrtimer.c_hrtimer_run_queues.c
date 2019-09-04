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
struct hrtimer_cpu_base {int softirq_activated; int /*<<< orphan*/  lock; int /*<<< orphan*/  softirq_expires_next; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_ACTIVE_HARD ; 
 int /*<<< orphan*/  HRTIMER_SOFTIRQ ; 
 int /*<<< orphan*/  KTIME_MAX ; 
 scalar_t__ __hrtimer_hres_active (struct hrtimer_cpu_base*) ; 
 int /*<<< orphan*/  __hrtimer_run_queues (struct hrtimer_cpu_base*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_bases ; 
 int /*<<< orphan*/  hrtimer_is_hres_enabled () ; 
 int /*<<< orphan*/  hrtimer_switch_to_hres () ; 
 int /*<<< orphan*/  hrtimer_update_base (struct hrtimer_cpu_base*) ; 
 int /*<<< orphan*/  ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raise_softirq_irqoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct hrtimer_cpu_base* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ tick_check_oneshot_change (int) ; 

void hrtimer_run_queues(void)
{
	struct hrtimer_cpu_base *cpu_base = this_cpu_ptr(&hrtimer_bases);
	unsigned long flags;
	ktime_t now;

	if (__hrtimer_hres_active(cpu_base))
		return;

	/*
	 * This _is_ ugly: We have to check periodically, whether we
	 * can switch to highres and / or nohz mode. The clocksource
	 * switch happens with xtime_lock held. Notification from
	 * there only sets the check bit in the tick_oneshot code,
	 * otherwise we might deadlock vs. xtime_lock.
	 */
	if (tick_check_oneshot_change(!hrtimer_is_hres_enabled())) {
		hrtimer_switch_to_hres();
		return;
	}

	raw_spin_lock_irqsave(&cpu_base->lock, flags);
	now = hrtimer_update_base(cpu_base);

	if (!ktime_before(now, cpu_base->softirq_expires_next)) {
		cpu_base->softirq_expires_next = KTIME_MAX;
		cpu_base->softirq_activated = 1;
		raise_softirq_irqoff(HRTIMER_SOFTIRQ);
	}

	__hrtimer_run_queues(cpu_base, now, flags, HRTIMER_ACTIVE_HARD);
	raw_spin_unlock_irqrestore(&cpu_base->lock, flags);
}