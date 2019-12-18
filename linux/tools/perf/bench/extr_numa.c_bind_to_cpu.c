#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  orig_mask ;
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  cpu_set_t ;
struct TYPE_3__ {int nr_cpus; } ;
struct TYPE_4__ {TYPE_1__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 TYPE_2__* g ; 
 int sched_getaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static cpu_set_t bind_to_cpu(int target_cpu)
{
	cpu_set_t orig_mask, mask;
	int ret;

	ret = sched_getaffinity(0, sizeof(orig_mask), &orig_mask);
	BUG_ON(ret);

	CPU_ZERO(&mask);

	if (target_cpu == -1) {
		int cpu;

		for (cpu = 0; cpu < g->p.nr_cpus; cpu++)
			CPU_SET(cpu, &mask);
	} else {
		BUG_ON(target_cpu < 0 || target_cpu >= g->p.nr_cpus);
		CPU_SET(target_cpu, &mask);
	}

	ret = sched_setaffinity(0, sizeof(mask), &mask);
	BUG_ON(ret);

	return orig_mask;
}