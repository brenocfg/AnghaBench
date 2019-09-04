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

/* Variables and functions */
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int debug_locks_off () ; 
 int /*<<< orphan*/  lockdep_lock ; 

__attribute__((used)) static inline int debug_locks_off_graph_unlock(void)
{
	int ret = debug_locks_off();

	arch_spin_unlock(&lockdep_lock);

	return ret;
}