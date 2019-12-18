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
 int /*<<< orphan*/  CPUINFO_MAX_FREQ ; 
 int /*<<< orphan*/  CPUINFO_MIN_FREQ ; 
 int EINVAL ; 
 int ENODEV ; 
 unsigned long sysfs_cpufreq_get_one_value (unsigned int,int /*<<< orphan*/ ) ; 

int cpufreq_get_hardware_limits(unsigned int cpu,
				unsigned long *min,
				unsigned long *max)
{
	if ((!min) || (!max))
		return -EINVAL;

	*min = sysfs_cpufreq_get_one_value(cpu, CPUINFO_MIN_FREQ);
	if (!*min)
		return -ENODEV;

	*max = sysfs_cpufreq_get_one_value(cpu, CPUINFO_MAX_FREQ);
	if (!*max)
		return -ENODEV;

	return 0;
}