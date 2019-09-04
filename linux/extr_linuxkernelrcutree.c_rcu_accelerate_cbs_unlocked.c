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
struct rcu_state {int /*<<< orphan*/  gp_seq; } ;
struct rcu_node {int dummy; } ;
struct rcu_data {int /*<<< orphan*/  cblist; int /*<<< orphan*/  gp_seq_needed; int /*<<< orphan*/  gpwrap; } ;

/* Variables and functions */
 scalar_t__ ULONG_CMP_GE (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  lockdep_assert_irqs_disabled () ; 
 int /*<<< orphan*/  raw_spin_lock_rcu_node (struct rcu_node*) ; 
 int /*<<< orphan*/  raw_spin_unlock_rcu_node (struct rcu_node*) ; 
 int rcu_accelerate_cbs (struct rcu_state*,struct rcu_node*,struct rcu_data*) ; 
 int /*<<< orphan*/  rcu_gp_kthread_wake (struct rcu_state*) ; 
 int /*<<< orphan*/  rcu_segcblist_accelerate (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long rcu_seq_snap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcu_accelerate_cbs_unlocked(struct rcu_state *rsp,
					struct rcu_node *rnp,
					struct rcu_data *rdp)
{
	unsigned long c;
	bool needwake;

	lockdep_assert_irqs_disabled();
	c = rcu_seq_snap(&rsp->gp_seq);
	if (!rdp->gpwrap && ULONG_CMP_GE(rdp->gp_seq_needed, c)) {
		/* Old request still live, so mark recent callbacks. */
		(void)rcu_segcblist_accelerate(&rdp->cblist, c);
		return;
	}
	raw_spin_lock_rcu_node(rnp); /* irqs already disabled. */
	needwake = rcu_accelerate_cbs(rsp, rnp, rdp);
	raw_spin_unlock_rcu_node(rnp); /* irqs remain disabled. */
	if (needwake)
		rcu_gp_kthread_wake(rsp);
}