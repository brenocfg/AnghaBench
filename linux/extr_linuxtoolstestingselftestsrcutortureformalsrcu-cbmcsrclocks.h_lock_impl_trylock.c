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
struct lock_impl {int locked; } ;

/* Variables and functions */
 int /*<<< orphan*/  __CPROVER_atomic_begin () ; 
 int /*<<< orphan*/  __CPROVER_atomic_end () ; 
 int /*<<< orphan*/  __CPROVER_fence (char*,char*) ; 

__attribute__((used)) static inline bool lock_impl_trylock(struct lock_impl *lock)
{
#ifdef RUN
	/* TODO: Should this be a test and set? */
	return __sync_bool_compare_and_swap(&lock->locked, false, true);
#else
	__CPROVER_atomic_begin();
	bool old_locked = lock->locked;
	lock->locked = true;
	__CPROVER_atomic_end();

	/* Minimal barrier to prevent accesses leaking out of lock. */
	__CPROVER_fence("RRfence", "RWfence");

	return !old_locked;
#endif
}