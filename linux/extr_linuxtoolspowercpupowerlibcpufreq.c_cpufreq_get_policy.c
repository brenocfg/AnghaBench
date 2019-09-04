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
struct cpufreq_policy {struct cpufreq_policy* governor; void* max; void* min; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCALING_GOVERNOR ; 
 int /*<<< orphan*/  SCALING_MAX_FREQ ; 
 int /*<<< orphan*/  SCALING_MIN_FREQ ; 
 int /*<<< orphan*/  free (struct cpufreq_policy*) ; 
 struct cpufreq_policy* malloc (int) ; 
 struct cpufreq_policy* sysfs_cpufreq_get_one_string (unsigned int,int /*<<< orphan*/ ) ; 
 void* sysfs_cpufreq_get_one_value (unsigned int,int /*<<< orphan*/ ) ; 

struct cpufreq_policy *cpufreq_get_policy(unsigned int cpu)
{
	struct cpufreq_policy *policy;

	policy = malloc(sizeof(struct cpufreq_policy));
	if (!policy)
		return NULL;

	policy->governor = sysfs_cpufreq_get_one_string(cpu, SCALING_GOVERNOR);
	if (!policy->governor) {
		free(policy);
		return NULL;
	}
	policy->min = sysfs_cpufreq_get_one_value(cpu, SCALING_MIN_FREQ);
	policy->max = sysfs_cpufreq_get_one_value(cpu, SCALING_MAX_FREQ);
	if ((!policy->min) || (!policy->max)) {
		free(policy->governor);
		free(policy);
		return NULL;
	}

	return policy;
}