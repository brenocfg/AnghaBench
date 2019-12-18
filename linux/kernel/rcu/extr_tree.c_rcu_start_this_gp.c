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
struct rcu_node {unsigned long gp_seq_needed; struct rcu_node* parent; int /*<<< orphan*/  gp_seq; } ;
struct rcu_data {unsigned long gp_seq_needed; } ;
struct TYPE_2__ {int gp_flags; int /*<<< orphan*/  gp_seq; int /*<<< orphan*/  name; int /*<<< orphan*/  gp_kthread; int /*<<< orphan*/  gp_req_activity; } ;

/* Variables and functions */
 int RCU_GP_FLAG_INIT ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPS (char*) ; 
 scalar_t__ ULONG_CMP_GE (unsigned long,unsigned long) ; 
 scalar_t__ ULONG_CMP_LT (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  raw_lockdep_assert_held_rcu_node (struct rcu_node*) ; 
 int /*<<< orphan*/  raw_spin_lock_rcu_node (struct rcu_node*) ; 
 int /*<<< orphan*/  raw_spin_unlock_rcu_node (struct rcu_node*) ; 
 scalar_t__ rcu_gp_in_progress () ; 
 int /*<<< orphan*/  rcu_seq_current (int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_seq_started (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ rcu_seq_state (int /*<<< orphan*/ ) ; 
 TYPE_1__ rcu_state ; 
 int /*<<< orphan*/  trace_rcu_grace_period (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_rcu_this_gp (struct rcu_node*,struct rcu_data*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rcu_start_this_gp(struct rcu_node *rnp_start, struct rcu_data *rdp,
			      unsigned long gp_seq_req)
{
	bool ret = false;
	struct rcu_node *rnp;

	/*
	 * Use funnel locking to either acquire the root rcu_node
	 * structure's lock or bail out if the need for this grace period
	 * has already been recorded -- or if that grace period has in
	 * fact already started.  If there is already a grace period in
	 * progress in a non-leaf node, no recording is needed because the
	 * end of the grace period will scan the leaf rcu_node structures.
	 * Note that rnp_start->lock must not be released.
	 */
	raw_lockdep_assert_held_rcu_node(rnp_start);
	trace_rcu_this_gp(rnp_start, rdp, gp_seq_req, TPS("Startleaf"));
	for (rnp = rnp_start; 1; rnp = rnp->parent) {
		if (rnp != rnp_start)
			raw_spin_lock_rcu_node(rnp);
		if (ULONG_CMP_GE(rnp->gp_seq_needed, gp_seq_req) ||
		    rcu_seq_started(&rnp->gp_seq, gp_seq_req) ||
		    (rnp != rnp_start &&
		     rcu_seq_state(rcu_seq_current(&rnp->gp_seq)))) {
			trace_rcu_this_gp(rnp, rdp, gp_seq_req,
					  TPS("Prestarted"));
			goto unlock_out;
		}
		rnp->gp_seq_needed = gp_seq_req;
		if (rcu_seq_state(rcu_seq_current(&rnp->gp_seq))) {
			/*
			 * We just marked the leaf or internal node, and a
			 * grace period is in progress, which means that
			 * rcu_gp_cleanup() will see the marking.  Bail to
			 * reduce contention.
			 */
			trace_rcu_this_gp(rnp_start, rdp, gp_seq_req,
					  TPS("Startedleaf"));
			goto unlock_out;
		}
		if (rnp != rnp_start && rnp->parent != NULL)
			raw_spin_unlock_rcu_node(rnp);
		if (!rnp->parent)
			break;  /* At root, and perhaps also leaf. */
	}

	/* If GP already in progress, just leave, otherwise start one. */
	if (rcu_gp_in_progress()) {
		trace_rcu_this_gp(rnp, rdp, gp_seq_req, TPS("Startedleafroot"));
		goto unlock_out;
	}
	trace_rcu_this_gp(rnp, rdp, gp_seq_req, TPS("Startedroot"));
	WRITE_ONCE(rcu_state.gp_flags, rcu_state.gp_flags | RCU_GP_FLAG_INIT);
	rcu_state.gp_req_activity = jiffies;
	if (!rcu_state.gp_kthread) {
		trace_rcu_this_gp(rnp, rdp, gp_seq_req, TPS("NoGPkthread"));
		goto unlock_out;
	}
	trace_rcu_grace_period(rcu_state.name, READ_ONCE(rcu_state.gp_seq), TPS("newreq"));
	ret = true;  /* Caller must wake GP kthread. */
unlock_out:
	/* Push furthest requested GP to leaf node and rcu_data structure. */
	if (ULONG_CMP_LT(gp_seq_req, rnp->gp_seq_needed)) {
		rnp_start->gp_seq_needed = rnp->gp_seq_needed;
		rdp->gp_seq_needed = rnp->gp_seq_needed;
	}
	if (rnp != rnp_start)
		raw_spin_unlock_rcu_node(rnp);
	return ret;
}