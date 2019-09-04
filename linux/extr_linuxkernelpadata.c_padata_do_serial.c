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
struct parallel_data {TYPE_2__* pinst; int /*<<< orphan*/  reorder_objects; int /*<<< orphan*/  pqueue; } ;
struct padata_priv {int cpu; int /*<<< orphan*/  list; struct parallel_data* pd; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct padata_parallel_queue {int /*<<< orphan*/  reorder_work; TYPE_1__ reorder; } ;
struct TYPE_4__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  padata_reorder (struct parallel_data*) ; 
 struct padata_parallel_queue* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  queue_work_on (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void padata_do_serial(struct padata_priv *padata)
{
	int cpu;
	struct padata_parallel_queue *pqueue;
	struct parallel_data *pd;
	int reorder_via_wq = 0;

	pd = padata->pd;

	cpu = get_cpu();

	/* We need to run on the same CPU padata_do_parallel(.., padata, ..)
	 * was called on -- or, at least, enqueue the padata object into the
	 * correct per-cpu queue.
	 */
	if (cpu != padata->cpu) {
		reorder_via_wq = 1;
		cpu = padata->cpu;
	}

	pqueue = per_cpu_ptr(pd->pqueue, cpu);

	spin_lock(&pqueue->reorder.lock);
	atomic_inc(&pd->reorder_objects);
	list_add_tail(&padata->list, &pqueue->reorder.list);
	spin_unlock(&pqueue->reorder.lock);

	put_cpu();

	/* If we're running on the wrong CPU, call padata_reorder() via a
	 * kernel worker.
	 */
	if (reorder_via_wq)
		queue_work_on(cpu, pd->pinst->wq, &pqueue->reorder_work);
	else
		padata_reorder(pd);
}