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
struct rcu_state {int dummy; } ;
struct rcu_node {int /*<<< orphan*/  gp_seq; } ;
struct rcu_data {scalar_t__ gp_seq; int /*<<< orphan*/  gpwrap; struct rcu_node* mynode; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int __note_gp_changes (struct rcu_state*,struct rcu_node*,struct rcu_data*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  raw_spin_trylock_rcu_node (struct rcu_node*) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore_rcu_node (struct rcu_node*,unsigned long) ; 
 int /*<<< orphan*/  rcu_gp_kthread_wake (struct rcu_state*) ; 
 scalar_t__ rcu_seq_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void note_gp_changes(struct rcu_state *rsp, struct rcu_data *rdp)
{
	unsigned long flags;
	bool needwake;
	struct rcu_node *rnp;

	local_irq_save(flags);
	rnp = rdp->mynode;
	if ((rdp->gp_seq == rcu_seq_current(&rnp->gp_seq) &&
	     !unlikely(READ_ONCE(rdp->gpwrap))) || /* w/out lock. */
	    !raw_spin_trylock_rcu_node(rnp)) { /* irqs already off, so later. */
		local_irq_restore(flags);
		return;
	}
	needwake = __note_gp_changes(rsp, rnp, rdp);
	raw_spin_unlock_irqrestore_rcu_node(rnp, flags);
	if (needwake)
		rcu_gp_kthread_wake(rsp);
}