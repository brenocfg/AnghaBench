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
struct cpufreq_policy {int /*<<< orphan*/  governor; } ;

/* Variables and functions */
 int ENODEV ; 
 int SYSFS_PATH_MAX ; 
 int /*<<< orphan*/  WRITE_SCALING_SET_SPEED ; 
 struct cpufreq_policy* cpufreq_get_policy (unsigned int) ; 
 int cpufreq_modify_policy_governor (unsigned int,char*) ; 
 int /*<<< orphan*/  cpufreq_put_policy (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int sysfs_cpufreq_write_one_value (unsigned int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int cpufreq_set_frequency(unsigned int cpu, unsigned long target_frequency)
{
	struct cpufreq_policy *pol = cpufreq_get_policy(cpu);
	char userspace_gov[] = "userspace";
	char freq[SYSFS_PATH_MAX];
	int ret;

	if (!pol)
		return -ENODEV;

	if (strncmp(pol->governor, userspace_gov, 9) != 0) {
		ret = cpufreq_modify_policy_governor(cpu, userspace_gov);
		if (ret) {
			cpufreq_put_policy(pol);
			return ret;
		}
	}

	cpufreq_put_policy(pol);

	snprintf(freq, SYSFS_PATH_MAX, "%lu", target_frequency);

	return sysfs_cpufreq_write_one_value(cpu, WRITE_SCALING_SET_SPEED,
					     freq, strlen(freq));
}