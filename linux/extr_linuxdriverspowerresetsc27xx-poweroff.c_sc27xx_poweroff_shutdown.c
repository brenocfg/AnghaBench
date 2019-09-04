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

__attribute__((used)) static void sc27xx_poweroff_shutdown(void)
{
#ifdef CONFIG_PM_SLEEP_SMP
	int cpu = smp_processor_id();

	freeze_secondary_cpus(cpu);
#endif
}