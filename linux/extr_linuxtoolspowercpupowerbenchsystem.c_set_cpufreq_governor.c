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
 scalar_t__ cpufreq_modify_policy_governor (unsigned int,char*) ; 
 int cpupower_is_cpu_online (unsigned int) ; 
 int /*<<< orphan*/  dprintf (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

int set_cpufreq_governor(char *governor, unsigned int cpu)
{

	dprintf("set %s as cpufreq governor\n", governor);

	if (cpupower_is_cpu_online(cpu) != 1) {
		perror("cpufreq_cpu_exists");
		fprintf(stderr, "error: cpu %u does not exist\n", cpu);
		return -1;
	}

	if (cpufreq_modify_policy_governor(cpu, governor) != 0) {
		perror("cpufreq_modify_policy_governor");
		fprintf(stderr, "error: unable to set %s governor\n", governor);
		return -1;
	}

	return 0;
}