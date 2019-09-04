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
struct TYPE_2__ {int new_master; int state; } ;
struct dlm_ctxt {int joining_node; int /*<<< orphan*/  recovery_map; int /*<<< orphan*/  migration_wq; int /*<<< orphan*/  exit_domain_map; int /*<<< orphan*/  domain_map; int /*<<< orphan*/  live_nodes_map; int /*<<< orphan*/  name; TYPE_1__ reco; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int DLM_RECO_STATE_FINALIZE ; 
 int /*<<< orphan*/  __dlm_reset_recovery (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  __dlm_set_joining_node (struct dlm_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_do_local_recovery_cleanup (struct dlm_ctxt*,int) ; 
 int /*<<< orphan*/  dlm_hb_event_notify_attached (struct dlm_ctxt*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __dlm_hb_node_down(struct dlm_ctxt *dlm, int idx)
{
	assert_spin_locked(&dlm->spinlock);

	if (dlm->reco.new_master == idx) {
		mlog(0, "%s: recovery master %d just died\n",
		     dlm->name, idx);
		if (dlm->reco.state & DLM_RECO_STATE_FINALIZE) {
			/* finalize1 was reached, so it is safe to clear
			 * the new_master and dead_node.  that recovery
			 * is complete. */
			mlog(0, "%s: dead master %d had reached "
			     "finalize1 state, clearing\n", dlm->name, idx);
			dlm->reco.state &= ~DLM_RECO_STATE_FINALIZE;
			__dlm_reset_recovery(dlm);
		}
	}

	/* Clean up join state on node death. */
	if (dlm->joining_node == idx) {
		mlog(0, "Clearing join state for node %u\n", idx);
		__dlm_set_joining_node(dlm, DLM_LOCK_RES_OWNER_UNKNOWN);
	}

	/* check to see if the node is already considered dead */
	if (!test_bit(idx, dlm->live_nodes_map)) {
		mlog(0, "for domain %s, node %d is already dead. "
		     "another node likely did recovery already.\n",
		     dlm->name, idx);
		return;
	}

	/* check to see if we do not care about this node */
	if (!test_bit(idx, dlm->domain_map)) {
		/* This also catches the case that we get a node down
		 * but haven't joined the domain yet. */
		mlog(0, "node %u already removed from domain!\n", idx);
		return;
	}

	clear_bit(idx, dlm->live_nodes_map);

	/* make sure local cleanup occurs before the heartbeat events */
	if (!test_bit(idx, dlm->recovery_map))
		dlm_do_local_recovery_cleanup(dlm, idx);

	/* notify anything attached to the heartbeat events */
	dlm_hb_event_notify_attached(dlm, idx, 0);

	mlog(0, "node %u being removed from domain map!\n", idx);
	clear_bit(idx, dlm->domain_map);
	clear_bit(idx, dlm->exit_domain_map);
	/* wake up migration waiters if a node goes down.
	 * perhaps later we can genericize this for other waiters. */
	wake_up(&dlm->migration_wq);

	set_bit(idx, dlm->recovery_map);
}