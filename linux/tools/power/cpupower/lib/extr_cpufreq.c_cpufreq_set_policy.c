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
struct cpufreq_policy {unsigned long max; unsigned long min; int /*<<< orphan*/  governor; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SCALING_MIN_FREQ ; 
 int SYSFS_PATH_MAX ; 
 int /*<<< orphan*/  WRITE_SCALING_GOVERNOR ; 
 int /*<<< orphan*/  WRITE_SCALING_MAX_FREQ ; 
 int /*<<< orphan*/  WRITE_SCALING_MIN_FREQ ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 unsigned long sysfs_cpufreq_get_one_value (unsigned int,int /*<<< orphan*/ ) ; 
 int sysfs_cpufreq_write_one_value (unsigned int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ verify_gov (char*,int /*<<< orphan*/ ) ; 

int cpufreq_set_policy(unsigned int cpu, struct cpufreq_policy *policy)
{
	char min[SYSFS_PATH_MAX];
	char max[SYSFS_PATH_MAX];
	char gov[SYSFS_PATH_MAX];
	int ret;
	unsigned long old_min;
	int write_max_first;

	if (!policy || !(policy->governor))
		return -EINVAL;

	if (policy->max < policy->min)
		return -EINVAL;

	if (verify_gov(gov, policy->governor))
		return -EINVAL;

	snprintf(min, SYSFS_PATH_MAX, "%lu", policy->min);
	snprintf(max, SYSFS_PATH_MAX, "%lu", policy->max);

	old_min = sysfs_cpufreq_get_one_value(cpu, SCALING_MIN_FREQ);
	write_max_first = (old_min && (policy->max < old_min) ? 0 : 1);

	if (write_max_first) {
		ret = sysfs_cpufreq_write_one_value(cpu, WRITE_SCALING_MAX_FREQ,
						    max, strlen(max));
		if (ret)
			return ret;
	}

	ret = sysfs_cpufreq_write_one_value(cpu, WRITE_SCALING_MIN_FREQ, min,
					    strlen(min));
	if (ret)
		return ret;

	if (!write_max_first) {
		ret = sysfs_cpufreq_write_one_value(cpu, WRITE_SCALING_MAX_FREQ,
						    max, strlen(max));
		if (ret)
			return ret;
	}

	return sysfs_cpufreq_write_one_value(cpu, WRITE_SCALING_GOVERNOR,
					     gov, strlen(gov));
}