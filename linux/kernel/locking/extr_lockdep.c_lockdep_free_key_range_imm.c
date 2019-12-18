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
struct pending_free {int dummy; } ;
struct TYPE_2__ {struct pending_free* pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_zapped_classes (struct pending_free*) ; 
 int /*<<< orphan*/  __lockdep_free_key_range (struct pending_free*,void*,unsigned long) ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ delayed_free ; 
 int /*<<< orphan*/  init_data_structures_once () ; 
 int /*<<< orphan*/  lockdep_lock ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 

__attribute__((used)) static void lockdep_free_key_range_imm(void *start, unsigned long size)
{
	struct pending_free *pf = delayed_free.pf;
	unsigned long flags;

	init_data_structures_once();

	raw_local_irq_save(flags);
	arch_spin_lock(&lockdep_lock);
	__lockdep_free_key_range(pf, start, size);
	__free_zapped_classes(pf);
	arch_spin_unlock(&lockdep_lock);
	raw_local_irq_restore(flags);
}