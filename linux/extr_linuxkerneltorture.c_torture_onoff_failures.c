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

bool torture_onoff_failures(void)
{
#ifdef CONFIG_HOTPLUG_CPU
	return n_online_successes != n_online_attempts ||
	       n_offline_successes != n_offline_attempts;
#else /* #ifdef CONFIG_HOTPLUG_CPU */
	return false;
#endif /* #else #ifdef CONFIG_HOTPLUG_CPU */
}