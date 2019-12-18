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
struct parallel_data {int /*<<< orphan*/  pqueue; int /*<<< orphan*/  seq_nr; int /*<<< orphan*/  refcnt; TYPE_1__ cpumask; } ;
struct padata_priv {int cb_cpu; int cpu; int /*<<< orphan*/  list; int /*<<< orphan*/  seq_nr; struct parallel_data* pd; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct padata_parallel_queue {int /*<<< orphan*/  work; TYPE_2__ parallel; } ;
struct padata_instance {int flags; int /*<<< orphan*/  parallel_wq; int /*<<< orphan*/  pd; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MAX_OBJ_NUM ; 
 int PADATA_INIT ; 
 int PADATA_INVALID ; 
 int PADATA_RESET ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int cpumask_next (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int cpumask_weight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int padata_cpu_hash (struct parallel_data*,int /*<<< orphan*/ ) ; 
 struct padata_parallel_queue* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct parallel_data* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int padata_do_parallel(struct padata_instance *pinst,
		       struct padata_priv *padata, int *cb_cpu)
{
	int i, cpu, cpu_index, target_cpu, err;
	struct padata_parallel_queue *queue;
	struct parallel_data *pd;

	rcu_read_lock_bh();

	pd = rcu_dereference_bh(pinst->pd);

	err = -EINVAL;
	if (!(pinst->flags & PADATA_INIT) || pinst->flags & PADATA_INVALID)
		goto out;

	if (!cpumask_test_cpu(*cb_cpu, pd->cpumask.cbcpu)) {
		if (!cpumask_weight(pd->cpumask.cbcpu))
			goto out;

		/* Select an alternate fallback CPU and notify the caller. */
		cpu_index = *cb_cpu % cpumask_weight(pd->cpumask.cbcpu);

		cpu = cpumask_first(pd->cpumask.cbcpu);
		for (i = 0; i < cpu_index; i++)
			cpu = cpumask_next(cpu, pd->cpumask.cbcpu);

		*cb_cpu = cpu;
	}

	err =  -EBUSY;
	if ((pinst->flags & PADATA_RESET))
		goto out;

	if (atomic_read(&pd->refcnt) >= MAX_OBJ_NUM)
		goto out;

	err = 0;
	atomic_inc(&pd->refcnt);
	padata->pd = pd;
	padata->cb_cpu = *cb_cpu;

	padata->seq_nr = atomic_inc_return(&pd->seq_nr);
	target_cpu = padata_cpu_hash(pd, padata->seq_nr);
	padata->cpu = target_cpu;
	queue = per_cpu_ptr(pd->pqueue, target_cpu);

	spin_lock(&queue->parallel.lock);
	list_add_tail(&padata->list, &queue->parallel.list);
	spin_unlock(&queue->parallel.lock);

	queue_work(pinst->parallel_wq, &queue->work);

out:
	rcu_read_unlock_bh();

	return err;
}