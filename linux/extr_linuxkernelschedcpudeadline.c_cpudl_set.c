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
typedef  void* u64 ;
struct cpudl {int /*<<< orphan*/  lock; TYPE_1__* elements; int /*<<< orphan*/  free_cpus; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int idx; int cpu; void* dl; } ;

/* Variables and functions */
 int IDX_INVALID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_present (int) ; 
 int /*<<< orphan*/  cpudl_heapify (struct cpudl*,int) ; 
 int /*<<< orphan*/  cpudl_heapify_up (struct cpudl*,int) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void cpudl_set(struct cpudl *cp, int cpu, u64 dl)
{
	int old_idx;
	unsigned long flags;

	WARN_ON(!cpu_present(cpu));

	raw_spin_lock_irqsave(&cp->lock, flags);

	old_idx = cp->elements[cpu].idx;
	if (old_idx == IDX_INVALID) {
		int new_idx = cp->size++;

		cp->elements[new_idx].dl = dl;
		cp->elements[new_idx].cpu = cpu;
		cp->elements[cpu].idx = new_idx;
		cpudl_heapify_up(cp, new_idx);
		cpumask_clear_cpu(cpu, cp->free_cpus);
	} else {
		cp->elements[old_idx].dl = dl;
		cpudl_heapify(cp, old_idx);
	}

	raw_spin_unlock_irqrestore(&cp->lock, flags);
}