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
struct rcu_state {int /*<<< orphan*/  gp_flags; int /*<<< orphan*/  n_force_qs; int /*<<< orphan*/  gp_activity; } ;
struct rcu_node {int dummy; } ;

/* Variables and functions */
 int RCU_GP_FLAG_FQS ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dyntick_save_progress_counter ; 
 int /*<<< orphan*/  force_qs_rnp (struct rcu_state*,int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  raw_spin_lock_irq_rcu_node (struct rcu_node*) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq_rcu_node (struct rcu_node*) ; 
 struct rcu_node* rcu_get_root (struct rcu_state*) ; 
 int /*<<< orphan*/  rcu_implicit_dynticks_qs ; 

__attribute__((used)) static void rcu_gp_fqs(struct rcu_state *rsp, bool first_time)
{
	struct rcu_node *rnp = rcu_get_root(rsp);

	WRITE_ONCE(rsp->gp_activity, jiffies);
	rsp->n_force_qs++;
	if (first_time) {
		/* Collect dyntick-idle snapshots. */
		force_qs_rnp(rsp, dyntick_save_progress_counter);
	} else {
		/* Handle dyntick-idle and offline CPUs. */
		force_qs_rnp(rsp, rcu_implicit_dynticks_qs);
	}
	/* Clear flag to prevent immediate re-entry. */
	if (READ_ONCE(rsp->gp_flags) & RCU_GP_FLAG_FQS) {
		raw_spin_lock_irq_rcu_node(rnp);
		WRITE_ONCE(rsp->gp_flags,
			   READ_ONCE(rsp->gp_flags) & ~RCU_GP_FLAG_FQS);
		raw_spin_unlock_irq_rcu_node(rnp);
	}
}