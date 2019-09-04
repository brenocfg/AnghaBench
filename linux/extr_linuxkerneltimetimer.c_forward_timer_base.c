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
struct timer_base {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void forward_timer_base(struct timer_base *base)
{
#ifdef CONFIG_NO_HZ_COMMON
	unsigned long jnow;

	/*
	 * We only forward the base when we are idle or have just come out of
	 * idle (must_forward_clk logic), and have a delta between base clock
	 * and jiffies. In the common case, run_timers will take care of it.
	 */
	if (likely(!base->must_forward_clk))
		return;

	jnow = READ_ONCE(jiffies);
	base->must_forward_clk = base->is_idle;
	if ((long)(jnow - base->clk) < 2)
		return;

	/*
	 * If the next expiry value is > jiffies, then we fast forward to
	 * jiffies otherwise we forward to the next expiry value.
	 */
	if (time_after(base->next_expiry, jnow))
		base->clk = jnow;
	else
		base->clk = base->next_expiry;
#endif
}