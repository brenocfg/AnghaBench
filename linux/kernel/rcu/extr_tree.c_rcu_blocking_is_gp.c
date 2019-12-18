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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PREEMPTION ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ RCU_SCHEDULER_INACTIVE ; 
 int /*<<< orphan*/  might_sleep () ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ rcu_scheduler_active ; 

__attribute__((used)) static int rcu_blocking_is_gp(void)
{
	int ret;

	if (IS_ENABLED(CONFIG_PREEMPTION))
		return rcu_scheduler_active == RCU_SCHEDULER_INACTIVE;
	might_sleep();  /* Check for RCU read-side critical section. */
	preempt_disable();
	ret = num_online_cpus() <= 1;
	preempt_enable();
	return ret;
}