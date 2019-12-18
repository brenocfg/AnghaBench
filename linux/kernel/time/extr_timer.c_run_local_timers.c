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
struct timer_base {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 size_t BASE_STD ; 
 int /*<<< orphan*/  CONFIG_NO_HZ_COMMON ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_SOFTIRQ ; 
 int /*<<< orphan*/  hrtimer_run_queues () ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  raise_softirq (int /*<<< orphan*/ ) ; 
 struct timer_base* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * timer_bases ; 

void run_local_timers(void)
{
	struct timer_base *base = this_cpu_ptr(&timer_bases[BASE_STD]);

	hrtimer_run_queues();
	/* Raise the softirq only if required. */
	if (time_before(jiffies, base->clk)) {
		if (!IS_ENABLED(CONFIG_NO_HZ_COMMON))
			return;
		/* CPU is awake, so check the deferrable base. */
		base++;
		if (time_before(jiffies, base->clk))
			return;
	}
	raise_softirq(TIMER_SOFTIRQ);
}