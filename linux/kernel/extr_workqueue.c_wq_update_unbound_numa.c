#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct workqueue_struct {int flags; int /*<<< orphan*/  mutex; struct pool_workqueue* dfl_pwq; int /*<<< orphan*/  name; TYPE_3__* unbound_attrs; } ;
struct workqueue_attrs {int /*<<< orphan*/ * cpumask; } ;
struct pool_workqueue {TYPE_1__* pool; } ;
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_6__ {scalar_t__ no_numa; } ;
struct TYPE_5__ {int /*<<< orphan*/  cpumask; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_2__* attrs; } ;

/* Variables and functions */
 int WQ_UNBOUND ; 
 struct pool_workqueue* alloc_unbound_pwq (struct workqueue_struct*,struct workqueue_attrs*) ; 
 int /*<<< orphan*/  copy_workqueue_attrs (struct workqueue_attrs*,TYPE_3__*) ; 
 int cpu_to_node (int) ; 
 scalar_t__ cpumask_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pwq (struct pool_workqueue*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pool_workqueue* numa_pwq_tbl_install (struct workqueue_struct*,int,struct pool_workqueue*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pwq_unlocked (struct pool_workqueue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct pool_workqueue* unbound_pwq_by_node (struct workqueue_struct*,int) ; 
 scalar_t__ wq_calc_node_cpumask (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wq_numa_enabled ; 
 int /*<<< orphan*/  wq_pool_mutex ; 
 struct workqueue_attrs* wq_update_unbound_numa_attrs_buf ; 

__attribute__((used)) static void wq_update_unbound_numa(struct workqueue_struct *wq, int cpu,
				   bool online)
{
	int node = cpu_to_node(cpu);
	int cpu_off = online ? -1 : cpu;
	struct pool_workqueue *old_pwq = NULL, *pwq;
	struct workqueue_attrs *target_attrs;
	cpumask_t *cpumask;

	lockdep_assert_held(&wq_pool_mutex);

	if (!wq_numa_enabled || !(wq->flags & WQ_UNBOUND) ||
	    wq->unbound_attrs->no_numa)
		return;

	/*
	 * We don't wanna alloc/free wq_attrs for each wq for each CPU.
	 * Let's use a preallocated one.  The following buf is protected by
	 * CPU hotplug exclusion.
	 */
	target_attrs = wq_update_unbound_numa_attrs_buf;
	cpumask = target_attrs->cpumask;

	copy_workqueue_attrs(target_attrs, wq->unbound_attrs);
	pwq = unbound_pwq_by_node(wq, node);

	/*
	 * Let's determine what needs to be done.  If the target cpumask is
	 * different from the default pwq's, we need to compare it to @pwq's
	 * and create a new one if they don't match.  If the target cpumask
	 * equals the default pwq's, the default pwq should be used.
	 */
	if (wq_calc_node_cpumask(wq->dfl_pwq->pool->attrs, node, cpu_off, cpumask)) {
		if (cpumask_equal(cpumask, pwq->pool->attrs->cpumask))
			return;
	} else {
		goto use_dfl_pwq;
	}

	/* create a new pwq */
	pwq = alloc_unbound_pwq(wq, target_attrs);
	if (!pwq) {
		pr_warn("workqueue: allocation failed while updating NUMA affinity of \"%s\"\n",
			wq->name);
		goto use_dfl_pwq;
	}

	/* Install the new pwq. */
	mutex_lock(&wq->mutex);
	old_pwq = numa_pwq_tbl_install(wq, node, pwq);
	goto out_unlock;

use_dfl_pwq:
	mutex_lock(&wq->mutex);
	spin_lock_irq(&wq->dfl_pwq->pool->lock);
	get_pwq(wq->dfl_pwq);
	spin_unlock_irq(&wq->dfl_pwq->pool->lock);
	old_pwq = numa_pwq_tbl_install(wq, node, wq->dfl_pwq);
out_unlock:
	mutex_unlock(&wq->mutex);
	put_pwq_unlocked(old_pwq);
}