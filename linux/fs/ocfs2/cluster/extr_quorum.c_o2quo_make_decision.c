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
struct work_struct {int dummy; } ;
struct o2quo_state {int qs_heartbeating; int qs_connected; int /*<<< orphan*/  qs_lock; int /*<<< orphan*/  qs_hb_bm; int /*<<< orphan*/  qs_conn_bm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 int O2NM_MAX_NODES ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int o2nm_this_node () ; 
 int /*<<< orphan*/  o2quo_fence_self () ; 
 struct o2quo_state o2quo_state ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void o2quo_make_decision(struct work_struct *work)
{
	int quorum;
	int lowest_hb, lowest_reachable = 0, fence = 0;
	struct o2quo_state *qs = &o2quo_state;

	spin_lock(&qs->qs_lock);

	lowest_hb = find_first_bit(qs->qs_hb_bm, O2NM_MAX_NODES);
	if (lowest_hb != O2NM_MAX_NODES)
		lowest_reachable = test_bit(lowest_hb, qs->qs_conn_bm);

	mlog(0, "heartbeating: %d, connected: %d, "
	     "lowest: %d (%sreachable)\n", qs->qs_heartbeating,
	     qs->qs_connected, lowest_hb, lowest_reachable ? "" : "un");

	if (!test_bit(o2nm_this_node(), qs->qs_hb_bm) ||
	    qs->qs_heartbeating == 1)
		goto out;

	if (qs->qs_heartbeating & 1) {
		/* the odd numbered cluster case is straight forward --
		 * if we can't talk to the majority we're hosed */
		quorum = (qs->qs_heartbeating + 1)/2;
		if (qs->qs_connected < quorum) {
			mlog(ML_ERROR, "fencing this node because it is "
			     "only connected to %u nodes and %u is needed "
			     "to make a quorum out of %u heartbeating nodes\n",
			     qs->qs_connected, quorum,
			     qs->qs_heartbeating);
			fence = 1;
		}
	} else {
		/* the even numbered cluster adds the possibility of each half
		 * of the cluster being able to talk amongst themselves.. in
		 * that case we're hosed if we can't talk to the group that has
		 * the lowest numbered node */
		quorum = qs->qs_heartbeating / 2;
		if (qs->qs_connected < quorum) {
			mlog(ML_ERROR, "fencing this node because it is "
			     "only connected to %u nodes and %u is needed "
			     "to make a quorum out of %u heartbeating nodes\n",
			     qs->qs_connected, quorum,
			     qs->qs_heartbeating);
			fence = 1;
		}
		else if ((qs->qs_connected == quorum) &&
			 !lowest_reachable) {
			mlog(ML_ERROR, "fencing this node because it is "
			     "connected to a half-quorum of %u out of %u "
			     "nodes which doesn't include the lowest active "
			     "node %u\n", quorum, qs->qs_heartbeating,
			     lowest_hb);
			fence = 1;
		}
	}

out:
	if (fence) {
		spin_unlock(&qs->qs_lock);
		o2quo_fence_self();
	} else {
		mlog(ML_NOTICE, "not fencing this node, heartbeating: %d, "
			"connected: %d, lowest: %d (%sreachable)\n",
			qs->qs_heartbeating, qs->qs_connected, lowest_hb,
			lowest_reachable ? "" : "un");
		spin_unlock(&qs->qs_lock);

	}

}