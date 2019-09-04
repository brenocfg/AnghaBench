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
struct cpufreq_affected_cpus {int cpu; struct cpufreq_affected_cpus* next; } ;

/* Variables and functions */
 int EINVAL ; 
 char* _ (char*) ; 
 struct cpufreq_affected_cpus* cpufreq_get_affected_cpus (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_put_affected_cpus (struct cpufreq_affected_cpus*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int get_affected_cpus(unsigned int cpu)
{
	struct cpufreq_affected_cpus *cpus = cpufreq_get_affected_cpus(cpu);

	printf(_("  CPUs which need to have their frequency coordinated by software: "));
	if (!cpus) {
		printf(_("Not Available\n"));
		return -EINVAL;
	}

	while (cpus->next) {
		printf("%d ", cpus->cpu);
		cpus = cpus->next;
	}
	printf("%d\n", cpus->cpu);
	cpufreq_put_affected_cpus(cpus);
	return 0;
}