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
typedef  int /*<<< orphan*/  set ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void find_cpus(unsigned int *first, unsigned int *last)
{
	unsigned int i;

	*first = -1U;
	*last = 0;
	for (i = 0; i < 4096; i++) {
		cpu_set_t set;
		CPU_ZERO(&set);
		CPU_SET(i, &set);
		if (sched_setaffinity(getpid(), sizeof(set), &set) == 0) {
			if (i < *first)
				*first = i;
			if (i > *last)
				*last = i;
		}
	}
}