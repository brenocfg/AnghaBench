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
typedef  int /*<<< orphan*/  torture_ofl_func ;

/* Variables and functions */
 int /*<<< orphan*/ * onoff_f ; 
 long onoff_holdoff ; 
 long onoff_interval ; 
 int /*<<< orphan*/  onoff_task ; 
 int torture_create_kthread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  torture_onoff ; 

int torture_onoff_init(long ooholdoff, long oointerval, torture_ofl_func *f)
{
#ifdef CONFIG_HOTPLUG_CPU
	onoff_holdoff = ooholdoff;
	onoff_interval = oointerval;
	onoff_f = f;
	if (onoff_interval <= 0)
		return 0;
	return torture_create_kthread(torture_onoff, NULL, onoff_task);
#else /* #ifdef CONFIG_HOTPLUG_CPU */
	return 0;
#endif /* #else #ifdef CONFIG_HOTPLUG_CPU */
}