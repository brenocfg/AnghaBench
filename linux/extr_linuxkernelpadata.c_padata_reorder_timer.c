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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcpu; } ;
struct parallel_data {unsigned int processed; int /*<<< orphan*/  pqueue; struct padata_instance* pinst; TYPE_1__ cpumask; } ;
struct padata_parallel_queue {int /*<<< orphan*/  reorder_work; } ;
struct padata_instance {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 unsigned int cpumask_weight (int /*<<< orphan*/ ) ; 
 struct parallel_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int get_cpu () ; 
 int padata_index_to_cpu (struct parallel_data*,unsigned int) ; 
 int /*<<< orphan*/  padata_reorder (struct parallel_data*) ; 
 struct parallel_data* pd ; 
 struct padata_parallel_queue* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  queue_work_on (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void padata_reorder_timer(struct timer_list *t)
{
	struct parallel_data *pd = from_timer(pd, t, timer);
	unsigned int weight;
	int target_cpu, cpu;

	cpu = get_cpu();

	/* We don't lock pd here to not interfere with parallel processing
	 * padata_reorder() calls on other CPUs. We just need any CPU out of
	 * the cpumask.pcpu set. It would be nice if it's the right one but
	 * it doesn't matter if we're off to the next one by using an outdated
	 * pd->processed value.
	 */
	weight = cpumask_weight(pd->cpumask.pcpu);
	target_cpu = padata_index_to_cpu(pd, pd->processed % weight);

	/* ensure to call the reorder callback on the correct CPU */
	if (cpu != target_cpu) {
		struct padata_parallel_queue *pqueue;
		struct padata_instance *pinst;

		/* The timer function is serialized wrt itself -- no locking
		 * needed.
		 */
		pinst = pd->pinst;
		pqueue = per_cpu_ptr(pd->pqueue, target_cpu);
		queue_work_on(target_cpu, pinst->wq, &pqueue->reorder_work);
	} else {
		padata_reorder(pd);
	}

	put_cpu();
}