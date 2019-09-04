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
struct workqueue_struct {int dummy; } ;
struct parallel_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cbcpu; int /*<<< orphan*/  pcpu; } ;
struct padata_instance {TYPE_1__ cpumask; int /*<<< orphan*/  lock; int /*<<< orphan*/  kobj; int /*<<< orphan*/  cpumask_change_notifier; scalar_t__ flags; struct workqueue_struct* wq; int /*<<< orphan*/  pd; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,struct cpumask const*) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct padata_instance*) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct padata_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct parallel_data* padata_alloc_pd (struct padata_instance*,struct cpumask const*,struct cpumask const*) ; 
 int /*<<< orphan*/  padata_attr_type ; 
 int /*<<< orphan*/  padata_validate_cpumask (struct padata_instance*,struct cpumask const*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct parallel_data*) ; 

__attribute__((used)) static struct padata_instance *padata_alloc(struct workqueue_struct *wq,
					    const struct cpumask *pcpumask,
					    const struct cpumask *cbcpumask)
{
	struct padata_instance *pinst;
	struct parallel_data *pd = NULL;

	pinst = kzalloc(sizeof(struct padata_instance), GFP_KERNEL);
	if (!pinst)
		goto err;

	if (!alloc_cpumask_var(&pinst->cpumask.pcpu, GFP_KERNEL))
		goto err_free_inst;
	if (!alloc_cpumask_var(&pinst->cpumask.cbcpu, GFP_KERNEL)) {
		free_cpumask_var(pinst->cpumask.pcpu);
		goto err_free_inst;
	}
	if (!padata_validate_cpumask(pinst, pcpumask) ||
	    !padata_validate_cpumask(pinst, cbcpumask))
		goto err_free_masks;

	pd = padata_alloc_pd(pinst, pcpumask, cbcpumask);
	if (!pd)
		goto err_free_masks;

	rcu_assign_pointer(pinst->pd, pd);

	pinst->wq = wq;

	cpumask_copy(pinst->cpumask.pcpu, pcpumask);
	cpumask_copy(pinst->cpumask.cbcpu, cbcpumask);

	pinst->flags = 0;

	BLOCKING_INIT_NOTIFIER_HEAD(&pinst->cpumask_change_notifier);
	kobject_init(&pinst->kobj, &padata_attr_type);
	mutex_init(&pinst->lock);

#ifdef CONFIG_HOTPLUG_CPU
	cpuhp_state_add_instance_nocalls_cpuslocked(hp_online, &pinst->node);
#endif
	return pinst;

err_free_masks:
	free_cpumask_var(pinst->cpumask.pcpu);
	free_cpumask_var(pinst->cpumask.cbcpu);
err_free_inst:
	kfree(pinst);
err:
	return NULL;
}