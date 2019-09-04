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
 unsigned int cpuidle_state_count (unsigned int) ; 
 long cpuidle_state_latency (unsigned int,unsigned int) ; 
 long cpuidle_state_time (unsigned int,unsigned int) ; 
 long cpuidle_state_usage (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void proc_cpuidle_cpu_output(unsigned int cpu)
{
	long max_allowed_cstate = 2000000000;
	unsigned int cstate, cstates;

	cstates = cpuidle_state_count(cpu);
	if (cstates == 0) {
		printf(_("CPU %u: No C-states info\n"), cpu);
		return;
	}

	printf(_("active state:            C0\n"));
	printf(_("max_cstate:              C%u\n"), cstates-1);
	printf(_("maximum allowed latency: %lu usec\n"), max_allowed_cstate);
	printf(_("states:\t\n"));
	for (cstate = 1; cstate < cstates; cstate++) {
		printf(_("    C%d:                  "
			 "type[C%d] "), cstate, cstate);
		printf(_("promotion[--] demotion[--] "));
		printf(_("latency[%03lu] "),
		       cpuidle_state_latency(cpu, cstate));
		printf(_("usage[%08lu] "),
		       cpuidle_state_usage(cpu, cstate));
		printf(_("duration[%020Lu] \n"),
		       cpuidle_state_time(cpu, cstate));
	}
}