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
 unsigned long UINT_MAX ; 
 char* _ (char*) ; 
 unsigned long cpufreq_get_transition_latency (unsigned int) ; 
 int /*<<< orphan*/  print_duration (unsigned long) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int get_latency(unsigned int cpu, unsigned int human)
{
	unsigned long latency = cpufreq_get_transition_latency(cpu);

	printf(_("  maximum transition latency: "));
	if (!latency || latency == UINT_MAX) {
		printf(_(" Cannot determine or is not supported.\n"));
		return -EINVAL;
	}

	if (human) {
		print_duration(latency);
		printf("\n");
	} else
		printf("%lu\n", latency);
	return 0;
}