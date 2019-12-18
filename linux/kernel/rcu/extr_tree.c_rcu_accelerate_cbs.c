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
struct rcu_node {int dummy; } ;
struct rcu_data {int /*<<< orphan*/  gp_seq; int /*<<< orphan*/  cblist; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  gp_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_WAIT_TAIL ; 
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  raw_lockdep_assert_held_rcu_node (struct rcu_node*) ; 
 int /*<<< orphan*/  rcu_lockdep_assert_cblist_protected (struct rcu_data*) ; 
 scalar_t__ rcu_segcblist_accelerate (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rcu_segcblist_pend_cbs (int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_segcblist_restempty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long rcu_seq_snap (int /*<<< orphan*/ *) ; 
 int rcu_start_this_gp (struct rcu_node*,struct rcu_data*,unsigned long) ; 
 TYPE_1__ rcu_state ; 
 int /*<<< orphan*/  trace_rcu_grace_period (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rcu_accelerate_cbs(struct rcu_node *rnp, struct rcu_data *rdp)
{
	unsigned long gp_seq_req;
	bool ret = false;

	rcu_lockdep_assert_cblist_protected(rdp);
	raw_lockdep_assert_held_rcu_node(rnp);

	/* If no pending (not yet ready to invoke) callbacks, nothing to do. */
	if (!rcu_segcblist_pend_cbs(&rdp->cblist))
		return false;

	/*
	 * Callbacks are often registered with incomplete grace-period
	 * information.  Something about the fact that getting exact
	 * information requires acquiring a global lock...  RCU therefore
	 * makes a conservative estimate of the grace period number at which
	 * a given callback will become ready to invoke.	The following
	 * code checks this estimate and improves it when possible, thus
	 * accelerating callback invocation to an earlier grace-period
	 * number.
	 */
	gp_seq_req = rcu_seq_snap(&rcu_state.gp_seq);
	if (rcu_segcblist_accelerate(&rdp->cblist, gp_seq_req))
		ret = rcu_start_this_gp(rnp, rdp, gp_seq_req);

	/* Trace depending on how much we were able to accelerate. */
	if (rcu_segcblist_restempty(&rdp->cblist, RCU_WAIT_TAIL))
		trace_rcu_grace_period(rcu_state.name, rdp->gp_seq, TPS("AccWaitCB"));
	else
		trace_rcu_grace_period(rcu_state.name, rdp->gp_seq, TPS("AccReadyCB"));
	return ret;
}