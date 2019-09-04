#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rcu_state {int /*<<< orphan*/  name; } ;
struct rcu_node {scalar_t__ gp_seq; int qsmask; int /*<<< orphan*/  gp_seq_needed; } ;
struct TYPE_4__ {int norm; } ;
struct TYPE_5__ {TYPE_1__ b; } ;
struct rcu_data {scalar_t__ gp_seq; int grpmask; int core_needs_qs; scalar_t__ gpwrap; int /*<<< orphan*/  gp_seq_needed; int /*<<< orphan*/  rcu_qs_ctr_snap; TYPE_2__ cpu_no_qs; } ;
struct TYPE_6__ {int /*<<< orphan*/  rcu_qs_ctr; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (scalar_t__) ; 
 int /*<<< orphan*/  TPS (char*) ; 
 scalar_t__ ULONG_CMP_GE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,int) ; 
 int /*<<< orphan*/  __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_lockdep_assert_held_rcu_node (struct rcu_node*) ; 
 int rcu_accelerate_cbs (struct rcu_state*,struct rcu_node*,struct rcu_data*) ; 
 int rcu_advance_cbs (struct rcu_state*,struct rcu_node*,struct rcu_data*) ; 
 TYPE_3__ rcu_dynticks ; 
 int /*<<< orphan*/  rcu_gpnum_ovf (struct rcu_node*,struct rcu_data*) ; 
 scalar_t__ rcu_seq_completed_gp (scalar_t__,scalar_t__) ; 
 scalar_t__ rcu_seq_new_gp (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_rcu_grace_period (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero_cpu_stall_ticks (struct rcu_data*) ; 

__attribute__((used)) static bool __note_gp_changes(struct rcu_state *rsp, struct rcu_node *rnp,
			      struct rcu_data *rdp)
{
	bool ret;
	bool need_gp;

	raw_lockdep_assert_held_rcu_node(rnp);

	if (rdp->gp_seq == rnp->gp_seq)
		return false; /* Nothing to do. */

	/* Handle the ends of any preceding grace periods first. */
	if (rcu_seq_completed_gp(rdp->gp_seq, rnp->gp_seq) ||
	    unlikely(READ_ONCE(rdp->gpwrap))) {
		ret = rcu_advance_cbs(rsp, rnp, rdp); /* Advance callbacks. */
		trace_rcu_grace_period(rsp->name, rdp->gp_seq, TPS("cpuend"));
	} else {
		ret = rcu_accelerate_cbs(rsp, rnp, rdp); /* Recent callbacks. */
	}

	/* Now handle the beginnings of any new-to-this-CPU grace periods. */
	if (rcu_seq_new_gp(rdp->gp_seq, rnp->gp_seq) ||
	    unlikely(READ_ONCE(rdp->gpwrap))) {
		/*
		 * If the current grace period is waiting for this CPU,
		 * set up to detect a quiescent state, otherwise don't
		 * go looking for one.
		 */
		trace_rcu_grace_period(rsp->name, rnp->gp_seq, TPS("cpustart"));
		need_gp = !!(rnp->qsmask & rdp->grpmask);
		rdp->cpu_no_qs.b.norm = need_gp;
		rdp->rcu_qs_ctr_snap = __this_cpu_read(rcu_dynticks.rcu_qs_ctr);
		rdp->core_needs_qs = need_gp;
		zero_cpu_stall_ticks(rdp);
	}
	rdp->gp_seq = rnp->gp_seq;  /* Remember new grace-period state. */
	if (ULONG_CMP_GE(rnp->gp_seq_needed, rdp->gp_seq_needed) || rdp->gpwrap)
		rdp->gp_seq_needed = rnp->gp_seq_needed;
	WRITE_ONCE(rdp->gpwrap, false);
	rcu_gpnum_ovf(rnp, rdp);
	return ret;
}