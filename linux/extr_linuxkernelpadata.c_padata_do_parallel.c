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
struct TYPE_3__ {int /*<<< orphan*/  cbcpu; } ;
struct parallel_data {int /*<<< orphan*/  pqueue; int /*<<< orphan*/  refcnt; TYPE_1__ cpumask; } ;
struct padata_priv {int cb_cpu; int cpu; int /*<<< orphan*/  list; struct parallel_data* pd; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct padata_parallel_queue {int /*<<< orphan*/  work; TYPE_2__ parallel; } ;
struct padata_instance {int flags; int /*<<< orphan*/  wq; int /*<<< orphan*/  pd; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MAX_OBJ_NUM ; 
 int PADATA_INIT ; 
 int PADATA_INVALID ; 
 int PADATA_RESET ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int padata_cpu_hash (struct parallel_data*) ; 
 struct padata_parallel_queue* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work_on (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct parallel_data* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int padata_do_parallel(struct padata_instance *pinst,
		       struct padata_priv *padata, int cb_cpu)
{
	int target_cpu, err;
	struct padata_parallel_queue *queue;
	struct parallel_data *pd;

	rcu_read_lock_bh();

	pd = rcu_dereference_bh(pinst->pd);

	err = -EINVAL;
	if (!(pinst->flags & PADATA_INIT) || pinst->flags & PADATA_INVALID)
		goto out;

	if (!cpumask_test_cpu(cb_cpu, pd->cpumask.cbcpu))
		goto out;

	err =  -EBUSY;
	if ((pinst->flags & PADATA_RESET))
		goto out;

	if (atomic_read(&pd->refcnt) >= MAX_OBJ_NUM)
		goto out;

	err = 0;
	atomic_inc(&pd->refcnt);
	padata->pd = pd;
	padata->cb_cpu = cb_cpu;

	target_cpu = padata_cpu_hash(pd);
	padata->cpu = target_cpu;
	queue = per_cpu_ptr(pd->pqueue, target_cpu);

	spin_lock(&queue->parallel.lock);
	list_add_tail(&padata->list, &queue->parallel.list);
	spin_unlock(&queue->parallel.lock);

	queue_work_on(target_cpu, pinst->wq, &queue->work);

out:
	rcu_read_unlock_bh();

	return err;
}