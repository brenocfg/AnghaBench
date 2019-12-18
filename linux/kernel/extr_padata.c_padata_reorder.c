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
struct parallel_data {int cpu; int /*<<< orphan*/  reorder_work; int /*<<< orphan*/  pqueue; int /*<<< orphan*/  lock; int /*<<< orphan*/  squeue; struct padata_instance* pinst; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct padata_serial_queue {int /*<<< orphan*/  work; TYPE_1__ serial; } ;
struct padata_priv {int cb_cpu; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct padata_parallel_queue {TYPE_2__ reorder; } ;
struct padata_instance {int /*<<< orphan*/  serial_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct padata_priv* padata_find_next (struct parallel_data*,int) ; 
 void* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work_on (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_trylock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void padata_reorder(struct parallel_data *pd)
{
	int cb_cpu;
	struct padata_priv *padata;
	struct padata_serial_queue *squeue;
	struct padata_instance *pinst = pd->pinst;
	struct padata_parallel_queue *next_queue;

	/*
	 * We need to ensure that only one cpu can work on dequeueing of
	 * the reorder queue the time. Calculating in which percpu reorder
	 * queue the next object will arrive takes some time. A spinlock
	 * would be highly contended. Also it is not clear in which order
	 * the objects arrive to the reorder queues. So a cpu could wait to
	 * get the lock just to notice that there is nothing to do at the
	 * moment. Therefore we use a trylock and let the holder of the lock
	 * care for all the objects enqueued during the holdtime of the lock.
	 */
	if (!spin_trylock_bh(&pd->lock))
		return;

	while (1) {
		padata = padata_find_next(pd, true);

		/*
		 * If the next object that needs serialization is parallel
		 * processed by another cpu and is still on it's way to the
		 * cpu's reorder queue, nothing to do for now.
		 */
		if (!padata)
			break;

		cb_cpu = padata->cb_cpu;
		squeue = per_cpu_ptr(pd->squeue, cb_cpu);

		spin_lock(&squeue->serial.lock);
		list_add_tail(&padata->list, &squeue->serial.list);
		spin_unlock(&squeue->serial.lock);

		queue_work_on(cb_cpu, pinst->serial_wq, &squeue->work);
	}

	spin_unlock_bh(&pd->lock);

	/*
	 * The next object that needs serialization might have arrived to
	 * the reorder queues in the meantime.
	 *
	 * Ensure reorder queue is read after pd->lock is dropped so we see
	 * new objects from another task in padata_do_serial.  Pairs with
	 * smp_mb__after_atomic in padata_do_serial.
	 */
	smp_mb();

	next_queue = per_cpu_ptr(pd->pqueue, pd->cpu);
	if (!list_empty(&next_queue->reorder.list) &&
	    padata_find_next(pd, false))
		queue_work(pinst->serial_wq, &pd->reorder_work);
}