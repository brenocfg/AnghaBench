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
 int /*<<< orphan*/  CONFIG_RCU_TORTURE_TEST ; 
 int /*<<< orphan*/  IS_BUILTIN (int /*<<< orphan*/ ) ; 
 int old_rt_runtime ; 
 int sysctl_sched_rt_runtime ; 

__attribute__((used)) static void rcu_torture_disable_rt_throttle(void)
{
	/*
	 * Disable RT throttling so that rcutorture's boost threads don't get
	 * throttled. Only possible if rcutorture is built-in otherwise the
	 * user should manually do this by setting the sched_rt_period_us and
	 * sched_rt_runtime sysctls.
	 */
	if (!IS_BUILTIN(CONFIG_RCU_TORTURE_TEST) || old_rt_runtime != -1)
		return;

	old_rt_runtime = sysctl_sched_rt_runtime;
	sysctl_sched_rt_runtime = -1;
}