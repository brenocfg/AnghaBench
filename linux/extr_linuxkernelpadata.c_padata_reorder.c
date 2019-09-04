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
struct parallel_data {int /*<<< orphan*/  timer; int /*<<< orphan*/  reorder_objects; int /*<<< orphan*/  lock; int /*<<< orphan*/  squeue; struct padata_instance* pinst; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct padata_serial_queue {int /*<<< orphan*/  work; TYPE_1__ serial; } ;
struct padata_priv {int cb_cpu; int /*<<< orphan*/  list; } ;
struct padata_instance {int flags; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  ENODATA ; 
 scalar_t__ HZ ; 
 int PADATA_RESET ; 
 int /*<<< orphan*/  PTR_ERR (struct padata_priv*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct padata_priv* padata_get_next (struct parallel_data*) ; 
 struct padata_serial_queue* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work_on (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
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
		padata = padata_get_next(pd);

		/*
		 * If the next object that needs serialization is parallel
		 * processed by another cpu and is still on it's way to the
		 * cpu's reorder queue, nothing to do for now.
		 */
		if (PTR_ERR(padata) == -EINPROGRESS)
			break;

		/*
		 * This cpu has to do the parallel processing of the next
		 * object. It's waiting in the cpu's parallelization queue,
		 * so exit immediately.
		 */
		if (PTR_ERR(padata) == -ENODATA) {
			del_timer(&pd->timer);
			spin_unlock_bh(&pd->lock);
			return;
		}

		cb_cpu = padata->cb_cpu;
		squeue = per_cpu_ptr(pd->squeue, cb_cpu);

		spin_lock(&squeue->serial.lock);
		list_add_tail(&padata->list, &squeue->serial.list);
		spin_unlock(&squeue->serial.lock);

		queue_work_on(cb_cpu, pinst->wq, &squeue->work);
	}

	spin_unlock_bh(&pd->lock);

	/*
	 * The next object that needs serialization might have arrived to
	 * the reorder queues in the meantime, we will be called again
	 * from the timer function if no one else cares for it.
	 */
	if (atomic_read(&pd->reorder_objects)
			&& !(pinst->flags & PADATA_RESET))
		mod_timer(&pd->timer, jiffies + HZ);
	else
		del_timer(&pd->timer);

	return;
}