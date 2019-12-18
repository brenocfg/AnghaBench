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
struct lockdep_map {int dummy; } ;
struct TYPE_2__ {struct pending_free* pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_zapped_classes (struct pending_free*) ; 
 int /*<<< orphan*/  __lockdep_reset_lock (struct pending_free*,struct lockdep_map*) ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ delayed_free ; 
 int /*<<< orphan*/  lockdep_lock ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 

__attribute__((used)) static void lockdep_reset_lock_imm(struct lockdep_map *lock)
{
	struct pending_free *pf = delayed_free.pf;
	unsigned long flags;

	raw_local_irq_save(flags);
	arch_spin_lock(&lockdep_lock);
	__lockdep_reset_lock(pf, lock);
	__free_zapped_classes(pf);
	arch_spin_unlock(&lockdep_lock);
	raw_local_irq_restore(flags);
}