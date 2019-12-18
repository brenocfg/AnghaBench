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
struct timer_list {int flags; int /*<<< orphan*/  expires; } ;
struct timer_base {int /*<<< orphan*/  cpu; int /*<<< orphan*/  next_expiry; int /*<<< orphan*/  is_idle; } ;

/* Variables and functions */
 int TIMER_DEFERRABLE ; 
 int /*<<< orphan*/  is_timers_nohz_active () ; 
 scalar_t__ tick_nohz_full_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_nohz_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
trigger_dyntick_cpu(struct timer_base *base, struct timer_list *timer)
{
	if (!is_timers_nohz_active())
		return;

	/*
	 * TODO: This wants some optimizing similar to the code below, but we
	 * will do that when we switch from push to pull for deferrable timers.
	 */
	if (timer->flags & TIMER_DEFERRABLE) {
		if (tick_nohz_full_cpu(base->cpu))
			wake_up_nohz_cpu(base->cpu);
		return;
	}

	/*
	 * We might have to IPI the remote CPU if the base is idle and the
	 * timer is not deferrable. If the other CPU is on the way to idle
	 * then it can't set base->is_idle as we hold the base lock:
	 */
	if (!base->is_idle)
		return;

	/* Check whether this is the new first expiring timer: */
	if (time_after_eq(timer->expires, base->next_expiry))
		return;

	/*
	 * Set the next expiry time and kick the CPU so it can reevaluate the
	 * wheel:
	 */
	base->next_expiry = timer->expires;
	wake_up_nohz_cpu(base->cpu);
}