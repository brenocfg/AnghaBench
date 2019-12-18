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
struct timer_base {int must_forward_clk; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int LVL_DEPTH ; 
 int collect_expired_timers (struct timer_base*,struct hlist_head*) ; 
 int /*<<< orphan*/  expire_timers (struct timer_base*,struct hlist_head*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_base_lock_expiry (struct timer_base*) ; 
 int /*<<< orphan*/  timer_base_unlock_expiry (struct timer_base*) ; 

__attribute__((used)) static inline void __run_timers(struct timer_base *base)
{
	struct hlist_head heads[LVL_DEPTH];
	int levels;

	if (!time_after_eq(jiffies, base->clk))
		return;

	timer_base_lock_expiry(base);
	raw_spin_lock_irq(&base->lock);

	/*
	 * timer_base::must_forward_clk must be cleared before running
	 * timers so that any timer functions that call mod_timer() will
	 * not try to forward the base. Idle tracking / clock forwarding
	 * logic is only used with BASE_STD timers.
	 *
	 * The must_forward_clk flag is cleared unconditionally also for
	 * the deferrable base. The deferrable base is not affected by idle
	 * tracking and never forwarded, so clearing the flag is a NOOP.
	 *
	 * The fact that the deferrable base is never forwarded can cause
	 * large variations in granularity for deferrable timers, but they
	 * can be deferred for long periods due to idle anyway.
	 */
	base->must_forward_clk = false;

	while (time_after_eq(jiffies, base->clk)) {

		levels = collect_expired_timers(base, heads);
		base->clk++;

		while (levels--)
			expire_timers(base, heads + levels);
	}
	raw_spin_unlock_irq(&base->lock);
	timer_base_unlock_expiry(base);
}