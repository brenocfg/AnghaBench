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
struct TYPE_2__ {int /*<<< orphan*/  lockdep_recursion; } ;

/* Variables and functions */
 int DEBUG_LOCKS_WARN_ON (int) ; 
 int /*<<< orphan*/  arch_spin_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 scalar_t__ debug_locks ; 
 int /*<<< orphan*/  lockdep_lock ; 

__attribute__((used)) static inline int graph_unlock(void)
{
	if (debug_locks && !arch_spin_is_locked(&lockdep_lock)) {
		/*
		 * The lockdep graph lock isn't locked while we expect it to
		 * be, we're confused now, bye!
		 */
		return DEBUG_LOCKS_WARN_ON(1);
	}

	current->lockdep_recursion--;
	arch_spin_unlock(&lockdep_lock);
	return 0;
}