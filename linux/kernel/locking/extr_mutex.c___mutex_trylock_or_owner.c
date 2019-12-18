#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct task_struct {int dummy; } ;
struct mutex {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOCKS_WARN_ON (unsigned long) ; 
 unsigned long MUTEX_FLAGS ; 
 unsigned long MUTEX_FLAG_HANDOFF ; 
 unsigned long MUTEX_FLAG_PICKUP ; 
 unsigned long __owner_flags (unsigned long) ; 
 struct task_struct* __owner_task (unsigned long) ; 
 unsigned long atomic_long_cmpxchg_acquire (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 scalar_t__ current ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline struct task_struct *__mutex_trylock_or_owner(struct mutex *lock)
{
	unsigned long owner, curr = (unsigned long)current;

	owner = atomic_long_read(&lock->owner);
	for (;;) { /* must loop, can race against a flag */
		unsigned long old, flags = __owner_flags(owner);
		unsigned long task = owner & ~MUTEX_FLAGS;

		if (task) {
			if (likely(task != curr))
				break;

			if (likely(!(flags & MUTEX_FLAG_PICKUP)))
				break;

			flags &= ~MUTEX_FLAG_PICKUP;
		} else {
#ifdef CONFIG_DEBUG_MUTEXES
			DEBUG_LOCKS_WARN_ON(flags & MUTEX_FLAG_PICKUP);
#endif
		}

		/*
		 * We set the HANDOFF bit, we must make sure it doesn't live
		 * past the point where we acquire it. This would be possible
		 * if we (accidentally) set the bit on an unlocked mutex.
		 */
		flags &= ~MUTEX_FLAG_HANDOFF;

		old = atomic_long_cmpxchg_acquire(&lock->owner, owner, curr | flags);
		if (old == owner)
			return NULL;

		owner = old;
	}

	return __owner_task(owner);
}