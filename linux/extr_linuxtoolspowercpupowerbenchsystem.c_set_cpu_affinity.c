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
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintf (char*,unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int set_cpu_affinity(unsigned int cpu)
{
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);

	dprintf("set affinity to cpu #%u\n", cpu);

	if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpuset) < 0) {
		perror("sched_setaffinity");
		fprintf(stderr, "warning: unable to set cpu affinity\n");
		return -1;
	}

	return 0;
}