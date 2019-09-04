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
 scalar_t__ CPU_COUNT_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_ISSET_S (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_present_set ; 
 int /*<<< orphan*/  cpu_selected_set ; 
 int /*<<< orphan*/  cpu_setsize ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int max_cpu_num ; 

void validate_cpu_selected_set(void)
{
	int cpu;

	if (CPU_COUNT_S(cpu_setsize, cpu_selected_set) == 0)
		errx(0, "no CPUs requested");

	for (cpu = 0; cpu <= max_cpu_num; ++cpu) {
		if (CPU_ISSET_S(cpu, cpu_setsize, cpu_selected_set))
			if (!CPU_ISSET_S(cpu, cpu_setsize, cpu_present_set))
				errx(1, "Requested cpu% is not present", cpu);
	}
}