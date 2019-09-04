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
struct cpudl {int size; int /*<<< orphan*/  lock; int /*<<< orphan*/  free_cpus; TYPE_1__* elements; } ;
struct TYPE_2__ {int idx; int cpu; int /*<<< orphan*/  dl; } ;

/* Variables and functions */
 int IDX_INVALID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_present (int) ; 
 int /*<<< orphan*/  cpudl_heapify (struct cpudl*,int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void cpudl_clear(struct cpudl *cp, int cpu)
{
	int old_idx, new_cpu;
	unsigned long flags;

	WARN_ON(!cpu_present(cpu));

	raw_spin_lock_irqsave(&cp->lock, flags);

	old_idx = cp->elements[cpu].idx;
	if (old_idx == IDX_INVALID) {
		/*
		 * Nothing to remove if old_idx was invalid.
		 * This could happen if a rq_offline_dl is
		 * called for a CPU without -dl tasks running.
		 */
	} else {
		new_cpu = cp->elements[cp->size - 1].cpu;
		cp->elements[old_idx].dl = cp->elements[cp->size - 1].dl;
		cp->elements[old_idx].cpu = new_cpu;
		cp->size--;
		cp->elements[new_cpu].idx = old_idx;
		cp->elements[cpu].idx = IDX_INVALID;
		cpudl_heapify(cp, old_idx);

		cpumask_set_cpu(cpu, cp->free_cpus);
	}
	raw_spin_unlock_irqrestore(&cp->lock, flags);
}