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
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int CPU_SETSIZE ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sched_getaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int pick_online_cpu(void)
{
	cpu_set_t mask;
	int cpu;

	CPU_ZERO(&mask);

	if (sched_getaffinity(0, sizeof(mask), &mask)) {
		perror("sched_getaffinity");
		return -1;
	}

	/* We prefer a primary thread, but skip 0 */
	for (cpu = 8; cpu < CPU_SETSIZE; cpu += 8)
		if (CPU_ISSET(cpu, &mask))
			return cpu;

	/* Search for anything, but in reverse */
	for (cpu = CPU_SETSIZE - 1; cpu >= 0; cpu--)
		if (CPU_ISSET(cpu, &mask))
			return cpu;

	printf("No cpus in affinity mask?!\n");
	return -1;
}