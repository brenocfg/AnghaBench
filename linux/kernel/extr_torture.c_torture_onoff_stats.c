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
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  max_offline ; 
 int /*<<< orphan*/  max_online ; 
 int /*<<< orphan*/  min_offline ; 
 int /*<<< orphan*/  min_online ; 
 int /*<<< orphan*/  n_offline_attempts ; 
 int /*<<< orphan*/  n_offline_successes ; 
 int /*<<< orphan*/  n_online_attempts ; 
 int /*<<< orphan*/  n_online_successes ; 
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sum_offline ; 
 int /*<<< orphan*/  sum_online ; 

void torture_onoff_stats(void)
{
#ifdef CONFIG_HOTPLUG_CPU
	pr_cont("onoff: %ld/%ld:%ld/%ld %d,%d:%d,%d %lu:%lu (HZ=%d) ",
		n_online_successes, n_online_attempts,
		n_offline_successes, n_offline_attempts,
		min_online, max_online,
		min_offline, max_offline,
		sum_online, sum_offline, HZ);
#endif /* #ifdef CONFIG_HOTPLUG_CPU */
}