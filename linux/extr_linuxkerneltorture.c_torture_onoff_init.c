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

int torture_onoff_init(long ooholdoff, long oointerval)
{
	int ret = 0;

#ifdef CONFIG_HOTPLUG_CPU
	onoff_holdoff = ooholdoff;
	onoff_interval = oointerval;
	if (onoff_interval <= 0)
		return 0;
	ret = torture_create_kthread(torture_onoff, NULL, onoff_task);
#endif /* #ifdef CONFIG_HOTPLUG_CPU */
	return ret;
}