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
struct rcu_head {int dummy; } ;
struct rcu_data {scalar_t__ qlen_last_fqs_check; scalar_t__ n_force_qs_snap; int /*<<< orphan*/  cblist; int /*<<< orphan*/  blimit; int /*<<< orphan*/  mynode; } ;
struct TYPE_2__ {scalar_t__ n_force_qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MAX_RCU_BLIMIT ; 
 scalar_t__ cpu_is_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invoke_rcu_core () ; 
 scalar_t__ irqs_disabled_flags (unsigned long) ; 
 int /*<<< orphan*/  note_gp_changes (struct rcu_data*) ; 
 scalar_t__ qhimark ; 
 int /*<<< orphan*/  rcu_accelerate_cbs_unlocked (int /*<<< orphan*/ ,struct rcu_data*) ; 
 int /*<<< orphan*/  rcu_force_quiescent_state () ; 
 int /*<<< orphan*/  rcu_gp_in_progress () ; 
 int /*<<< orphan*/  rcu_is_watching () ; 
 struct rcu_head* rcu_segcblist_first_pend_cb (int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_segcblist_n_cbs (int /*<<< orphan*/ *) ; 
 TYPE_1__ rcu_state ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __call_rcu_core(struct rcu_data *rdp, struct rcu_head *head,
			    unsigned long flags)
{
	/*
	 * If called from an extended quiescent state, invoke the RCU
	 * core in order to force a re-evaluation of RCU's idleness.
	 */
	if (!rcu_is_watching())
		invoke_rcu_core();

	/* If interrupts were disabled or CPU offline, don't invoke RCU core. */
	if (irqs_disabled_flags(flags) || cpu_is_offline(smp_processor_id()))
		return;

	/*
	 * Force the grace period if too many callbacks or too long waiting.
	 * Enforce hysteresis, and don't invoke rcu_force_quiescent_state()
	 * if some other CPU has recently done so.  Also, don't bother
	 * invoking rcu_force_quiescent_state() if the newly enqueued callback
	 * is the only one waiting for a grace period to complete.
	 */
	if (unlikely(rcu_segcblist_n_cbs(&rdp->cblist) >
		     rdp->qlen_last_fqs_check + qhimark)) {

		/* Are we ignoring a completed grace period? */
		note_gp_changes(rdp);

		/* Start a new grace period if one not already started. */
		if (!rcu_gp_in_progress()) {
			rcu_accelerate_cbs_unlocked(rdp->mynode, rdp);
		} else {
			/* Give the grace period a kick. */
			rdp->blimit = DEFAULT_MAX_RCU_BLIMIT;
			if (rcu_state.n_force_qs == rdp->n_force_qs_snap &&
			    rcu_segcblist_first_pend_cb(&rdp->cblist) != head)
				rcu_force_quiescent_state();
			rdp->n_force_qs_snap = rcu_state.n_force_qs;
			rdp->qlen_last_fqs_check = rcu_segcblist_n_cbs(&rdp->cblist);
		}
	}
}