#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvmet_fc_tgtport {TYPE_1__* ops; } ;
struct TYPE_2__ {int max_hw_queues; } ;

/* Variables and functions */
 int WORK_CPU_UNBOUND ; 
 scalar_t__ cpu_active (int) ; 
 int num_active_cpus () ; 
 int num_possible_cpus () ; 

__attribute__((used)) static int
nvmet_fc_queue_to_cpu(struct nvmet_fc_tgtport *tgtport, int qid)
{
	int cpu, idx, cnt;

	if (tgtport->ops->max_hw_queues == 1)
		return WORK_CPU_UNBOUND;

	/* Simple cpu selection based on qid modulo active cpu count */
	idx = !qid ? 0 : (qid - 1) % num_active_cpus();

	/* find the n'th active cpu */
	for (cpu = 0, cnt = 0; ; ) {
		if (cpu_active(cpu)) {
			if (cnt == idx)
				break;
			cnt++;
		}
		cpu = (cpu + 1) % num_possible_cpus();
	}

	return cpu;
}