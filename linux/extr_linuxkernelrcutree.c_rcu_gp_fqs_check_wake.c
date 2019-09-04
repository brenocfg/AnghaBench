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
struct rcu_state {int /*<<< orphan*/  gp_flags; } ;
struct rcu_node {int /*<<< orphan*/  qsmask; } ;

/* Variables and functions */
 int RCU_GP_FLAG_FQS ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 struct rcu_node* rcu_get_root (struct rcu_state*) ; 
 int /*<<< orphan*/  rcu_preempt_blocked_readers_cgp (struct rcu_node*) ; 

__attribute__((used)) static bool rcu_gp_fqs_check_wake(struct rcu_state *rsp, int *gfp)
{
	struct rcu_node *rnp = rcu_get_root(rsp);

	/* Someone like call_rcu() requested a force-quiescent-state scan. */
	*gfp = READ_ONCE(rsp->gp_flags);
	if (*gfp & RCU_GP_FLAG_FQS)
		return true;

	/* The current grace period has completed. */
	if (!READ_ONCE(rnp->qsmask) && !rcu_preempt_blocked_readers_cgp(rnp))
		return true;

	return false;
}