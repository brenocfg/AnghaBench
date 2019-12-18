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
 int SYSFS_PATH_MAX ; 
 int /*<<< orphan*/  WRITE_SCALING_MAX_FREQ ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int sysfs_cpufreq_write_one_value (unsigned int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int cpufreq_modify_policy_max(unsigned int cpu, unsigned long max_freq)
{
	char value[SYSFS_PATH_MAX];

	snprintf(value, SYSFS_PATH_MAX, "%lu", max_freq);

	return sysfs_cpufreq_write_one_value(cpu, WRITE_SCALING_MAX_FREQ,
					     value, strlen(value));
}