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
struct mcs_spinlock {int /*<<< orphan*/  locked; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 struct mcs_spinlock* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_mcs_spin_unlock_contended (int /*<<< orphan*/ *) ; 
 struct mcs_spinlock* cmpxchg_release (struct mcs_spinlock**,struct mcs_spinlock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline
void mcs_spin_unlock(struct mcs_spinlock **lock, struct mcs_spinlock *node)
{
	struct mcs_spinlock *next = READ_ONCE(node->next);

	if (likely(!next)) {
		/*
		 * Release the lock by setting it to NULL
		 */
		if (likely(cmpxchg_release(lock, node, NULL) == node))
			return;
		/* Wait until the next pointer is set */
		while (!(next = READ_ONCE(node->next)))
			cpu_relax();
	}

	/* Pass lock to next waiter. */
	arch_mcs_spin_unlock_contended(&next->locked);
}