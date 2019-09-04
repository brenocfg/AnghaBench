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
struct cpufreq_policy {int min; int max; int /*<<< orphan*/  governor; } ;

/* Variables and functions */
 char* _ (char*) ; 
 unsigned int count_cpus () ; 
 scalar_t__ cpufreq_get_hardware_limits (unsigned int,unsigned long*,unsigned long*) ; 
 struct cpufreq_policy* cpufreq_get_policy (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_put_policy (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void proc_cpufreq_output(void)
{
	unsigned int cpu, nr_cpus;
	struct cpufreq_policy *policy;
	unsigned int min_pctg = 0;
	unsigned int max_pctg = 0;
	unsigned long min, max;

	printf(_("          minimum CPU frequency  -  maximum CPU frequency  -  governor\n"));

	nr_cpus = count_cpus();
	for (cpu = 0; cpu < nr_cpus; cpu++) {
		policy = cpufreq_get_policy(cpu);
		if (!policy)
			continue;

		if (cpufreq_get_hardware_limits(cpu, &min, &max)) {
			max = 0;
		} else {
			min_pctg = (policy->min * 100) / max;
			max_pctg = (policy->max * 100) / max;
		}
		printf("CPU%3d    %9lu kHz (%3d %%)  -  %9lu kHz (%3d %%)  -  %s\n",
			cpu , policy->min, max ? min_pctg : 0, policy->max,
			max ? max_pctg : 0, policy->governor);

		cpufreq_put_policy(policy);
	}
}