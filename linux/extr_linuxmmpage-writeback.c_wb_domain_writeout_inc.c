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
struct wb_domain {scalar_t__ period_time; int /*<<< orphan*/  period_timer; int /*<<< orphan*/  completions; } ;
struct fprop_local_percpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fprop_inc_percpu_max (int /*<<< orphan*/ *,struct fprop_local_percpu*,unsigned int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ wp_next_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wb_domain_writeout_inc(struct wb_domain *dom,
				   struct fprop_local_percpu *completions,
				   unsigned int max_prop_frac)
{
	__fprop_inc_percpu_max(&dom->completions, completions,
			       max_prop_frac);
	/* First event after period switching was turned off? */
	if (unlikely(!dom->period_time)) {
		/*
		 * We can race with other __bdi_writeout_inc calls here but
		 * it does not cause any harm since the resulting time when
		 * timer will fire and what is in writeout_period_time will be
		 * roughly the same.
		 */
		dom->period_time = wp_next_time(jiffies);
		mod_timer(&dom->period_timer, dom->period_time);
	}
}