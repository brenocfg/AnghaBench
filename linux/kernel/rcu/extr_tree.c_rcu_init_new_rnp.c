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
struct rcu_node {long grpmask; long qsmaskinit; struct rcu_node* parent; int /*<<< orphan*/  wait_blkd_tasks; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_lockdep_assert_held_rcu_node (struct rcu_node*) ; 
 int /*<<< orphan*/  raw_spin_lock_rcu_node (struct rcu_node*) ; 
 int /*<<< orphan*/  raw_spin_unlock_rcu_node (struct rcu_node*) ; 

__attribute__((used)) static void rcu_init_new_rnp(struct rcu_node *rnp_leaf)
{
	long mask;
	long oldmask;
	struct rcu_node *rnp = rnp_leaf;

	raw_lockdep_assert_held_rcu_node(rnp_leaf);
	WARN_ON_ONCE(rnp->wait_blkd_tasks);
	for (;;) {
		mask = rnp->grpmask;
		rnp = rnp->parent;
		if (rnp == NULL)
			return;
		raw_spin_lock_rcu_node(rnp); /* Interrupts already disabled. */
		oldmask = rnp->qsmaskinit;
		rnp->qsmaskinit |= mask;
		raw_spin_unlock_rcu_node(rnp); /* Interrupts remain disabled. */
		if (oldmask)
			return;
	}
}