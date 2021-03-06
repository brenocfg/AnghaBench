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
 int EINVAL ; 
 int SYSFS_PATH_MAX ; 
 int /*<<< orphan*/  WRITE_SCALING_GOVERNOR ; 
 int strlen (char*) ; 
 int sysfs_cpufreq_write_one_value (unsigned int,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ verify_gov (char*,char*) ; 

int cpufreq_modify_policy_governor(unsigned int cpu, char *governor)
{
	char new_gov[SYSFS_PATH_MAX];

	if ((!governor) || (strlen(governor) > 19))
		return -EINVAL;

	if (verify_gov(new_gov, governor))
		return -EINVAL;

	return sysfs_cpufreq_write_one_value(cpu, WRITE_SCALING_GOVERNOR,
					     new_gov, strlen(new_gov));
}