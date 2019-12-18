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
typedef  int /*<<< orphan*/  cpuset ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int nr_cpus ; 
 int /*<<< orphan*/  sched_setaffinity (int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sched_next_online(int pid, int next_to_try)
{
	cpu_set_t cpuset;

	if (next_to_try == nr_cpus)
		return -1;

	while (next_to_try < nr_cpus) {
		CPU_ZERO(&cpuset);
		CPU_SET(next_to_try++, &cpuset);
		if (!sched_setaffinity(pid, sizeof(cpuset), &cpuset))
			break;
	}

	return next_to_try;
}