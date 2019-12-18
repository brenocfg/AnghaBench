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
struct TYPE_2__ {int /*<<< orphan*/  cbcpu; int /*<<< orphan*/  pcpu; } ;
struct padata_instance {int /*<<< orphan*/  parallel_wq; int /*<<< orphan*/  serial_wq; TYPE_1__ cpumask; int /*<<< orphan*/  pd; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuhp_state_remove_instance_nocalls (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp_online ; 
 int /*<<< orphan*/  kfree (struct padata_instance*) ; 
 int /*<<< orphan*/  padata_free_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padata_stop (struct padata_instance*) ; 

__attribute__((used)) static void __padata_free(struct padata_instance *pinst)
{
#ifdef CONFIG_HOTPLUG_CPU
	cpuhp_state_remove_instance_nocalls(hp_online, &pinst->node);
#endif

	padata_stop(pinst);
	padata_free_pd(pinst->pd);
	free_cpumask_var(pinst->cpumask.pcpu);
	free_cpumask_var(pinst->cpumask.cbcpu);
	destroy_workqueue(pinst->serial_wq);
	destroy_workqueue(pinst->parallel_wq);
	kfree(pinst);
}