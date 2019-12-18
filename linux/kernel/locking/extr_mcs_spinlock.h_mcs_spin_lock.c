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
struct mcs_spinlock {scalar_t__ locked; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ *,struct mcs_spinlock*) ; 
 int /*<<< orphan*/  arch_mcs_spin_lock_contended (scalar_t__*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct mcs_spinlock* xchg (struct mcs_spinlock**,struct mcs_spinlock*) ; 

__attribute__((used)) static inline
void mcs_spin_lock(struct mcs_spinlock **lock, struct mcs_spinlock *node)
{
	struct mcs_spinlock *prev;

	/* Init node */
	node->locked = 0;
	node->next   = NULL;

	/*
	 * We rely on the full barrier with global transitivity implied by the
	 * below xchg() to order the initialization stores above against any
	 * observation of @node. And to provide the ACQUIRE ordering associated
	 * with a LOCK primitive.
	 */
	prev = xchg(lock, node);
	if (likely(prev == NULL)) {
		/*
		 * Lock acquired, don't need to set node->locked to 1. Threads
		 * only spin on its own node->locked value for lock acquisition.
		 * However, since this thread can immediately acquire the lock
		 * and does not proceed to spin on its own node->locked, this
		 * value won't be used. If a debug mode is needed to
		 * audit lock status, then set node->locked value here.
		 */
		return;
	}
	WRITE_ONCE(prev->next, node);

	/* Wait until the lock holder passes the lock down. */
	arch_mcs_spin_lock_contended(&node->locked);
}