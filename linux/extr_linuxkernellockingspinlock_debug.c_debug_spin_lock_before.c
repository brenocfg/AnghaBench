#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ magic; scalar_t__ owner; scalar_t__ owner_cpu; } ;
typedef  TYPE_1__ raw_spinlock_t ;

/* Variables and functions */
 scalar_t__ SPINLOCK_MAGIC ; 
 int /*<<< orphan*/  SPIN_BUG_ON (int,TYPE_1__*,char*) ; 
 scalar_t__ current ; 
 scalar_t__ raw_smp_processor_id () ; 

__attribute__((used)) static inline void
debug_spin_lock_before(raw_spinlock_t *lock)
{
	SPIN_BUG_ON(lock->magic != SPINLOCK_MAGIC, lock, "bad magic");
	SPIN_BUG_ON(lock->owner == current, lock, "recursion");
	SPIN_BUG_ON(lock->owner_cpu == raw_smp_processor_id(),
							lock, "cpu recursion");
}