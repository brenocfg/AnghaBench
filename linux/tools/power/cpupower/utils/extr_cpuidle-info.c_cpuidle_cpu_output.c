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
 char* _ (char*) ; 
 int cpuidle_is_state_disabled (unsigned int,unsigned int) ; 
 unsigned int cpuidle_state_count (unsigned int) ; 
 char* cpuidle_state_desc (unsigned int,unsigned int) ; 
 char* cpuidle_state_latency (unsigned int,unsigned int) ; 
 char* cpuidle_state_name (unsigned int,unsigned int) ; 
 char* cpuidle_state_time (unsigned int,unsigned int) ; 
 char* cpuidle_state_usage (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void cpuidle_cpu_output(unsigned int cpu, int verbose)
{
	unsigned int idlestates, idlestate;
	char *tmp;

	idlestates = cpuidle_state_count(cpu);
	if (idlestates == 0) {
		printf(_("CPU %u: No idle states\n"), cpu);
		return;
	}

	printf(_("Number of idle states: %d\n"), idlestates);
	printf(_("Available idle states:"));
	for (idlestate = 0; idlestate < idlestates; idlestate++) {
		tmp = cpuidle_state_name(cpu, idlestate);
		if (!tmp)
			continue;
		printf(" %s", tmp);
		free(tmp);
	}
	printf("\n");

	if (!verbose)
		return;

	for (idlestate = 0; idlestate < idlestates; idlestate++) {
		int disabled = cpuidle_is_state_disabled(cpu, idlestate);
		/* Disabled interface not supported on older kernels */
		if (disabled < 0)
			disabled = 0;
		tmp = cpuidle_state_name(cpu, idlestate);
		if (!tmp)
			continue;
		printf("%s%s:\n", tmp, (disabled) ? " (DISABLED) " : "");
		free(tmp);

		tmp = cpuidle_state_desc(cpu, idlestate);
		if (!tmp)
			continue;
		printf(_("Flags/Description: %s\n"), tmp);
		free(tmp);

		printf(_("Latency: %lu\n"),
		       cpuidle_state_latency(cpu, idlestate));
		printf(_("Usage: %lu\n"),
		       cpuidle_state_usage(cpu, idlestate));
		printf(_("Duration: %llu\n"),
		       cpuidle_state_time(cpu, idlestate));
	}
}