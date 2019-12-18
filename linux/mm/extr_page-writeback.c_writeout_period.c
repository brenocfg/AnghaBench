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
struct wb_domain {int period_time; int /*<<< orphan*/  period_timer; int /*<<< orphan*/  completions; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int VM_COMPLETIONS_PERIOD_LEN ; 
 struct wb_domain* dom ; 
 scalar_t__ fprop_new_period (int /*<<< orphan*/ *,int) ; 
 struct wb_domain* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  period_timer ; 
 int wp_next_time (int) ; 

__attribute__((used)) static void writeout_period(struct timer_list *t)
{
	struct wb_domain *dom = from_timer(dom, t, period_timer);
	int miss_periods = (jiffies - dom->period_time) /
						 VM_COMPLETIONS_PERIOD_LEN;

	if (fprop_new_period(&dom->completions, miss_periods + 1)) {
		dom->period_time = wp_next_time(dom->period_time +
				miss_periods * VM_COMPLETIONS_PERIOD_LEN);
		mod_timer(&dom->period_timer, dom->period_time);
	} else {
		/*
		 * Aging has zeroed all fractions. Stop wasting CPU on period
		 * updates.
		 */
		dom->period_time = 0;
	}
}