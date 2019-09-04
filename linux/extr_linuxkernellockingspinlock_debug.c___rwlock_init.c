#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lock_class_key {int dummy; } ;
struct TYPE_3__ {int owner_cpu; int /*<<< orphan*/  owner; int /*<<< orphan*/  magic; scalar_t__ raw_lock; } ;
typedef  TYPE_1__ rwlock_t ;
typedef  scalar_t__ arch_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  RWLOCK_MAGIC ; 
 int /*<<< orphan*/  SPINLOCK_OWNER_INIT ; 
 scalar_t__ __ARCH_RW_LOCK_UNLOCKED ; 

void __rwlock_init(rwlock_t *lock, const char *name,
		   struct lock_class_key *key)
{
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	/*
	 * Make sure we are not reinitializing a held lock:
	 */
	debug_check_no_locks_freed((void *)lock, sizeof(*lock));
	lockdep_init_map(&lock->dep_map, name, key, 0);
#endif
	lock->raw_lock = (arch_rwlock_t) __ARCH_RW_LOCK_UNLOCKED;
	lock->magic = RWLOCK_MAGIC;
	lock->owner = SPINLOCK_OWNER_INIT;
	lock->owner_cpu = -1;
}