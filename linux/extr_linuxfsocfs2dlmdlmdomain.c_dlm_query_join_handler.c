#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct o2net_msg {scalar_t__ buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  pv_minor; } ;
struct dlm_query_join_request {int node_idx; TYPE_2__ fs_proto; TYPE_2__ dlm_proto; int /*<<< orphan*/  node_map; int /*<<< orphan*/  name_len; int /*<<< orphan*/  domain; } ;
struct dlm_query_join_packet {void* code; int /*<<< orphan*/  fs_minor; int /*<<< orphan*/  dlm_minor; } ;
struct TYPE_3__ {int state; } ;
struct dlm_ctxt {scalar_t__ dlm_state; scalar_t__ joining_node; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  fs_locking_proto; int /*<<< orphan*/  dlm_locking_proto; int /*<<< orphan*/  domain_map; int /*<<< orphan*/  recovery_map; TYPE_1__ reco; } ;

/* Variables and functions */
 scalar_t__ DLM_CTXT_LEAVING ; 
 scalar_t__ DLM_CTXT_NEW ; 
 scalar_t__ DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int DLM_RECO_STATE_ACTIVE ; 
 void* JOIN_DISALLOW ; 
 void* JOIN_OK ; 
 void* JOIN_OK_NO_MAP ; 
 void* JOIN_PROTOCOL_MISMATCH ; 
 scalar_t__ O2NM_MAX_NODES ; 
 struct dlm_ctxt* __dlm_lookup_domain_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dlm_set_joining_node (struct dlm_ctxt*,int) ; 
 int /*<<< orphan*/  byte_test_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_domain_lock ; 
 int /*<<< orphan*/  dlm_query_join_packet_to_wire (struct dlm_query_join_packet*,int*) ; 
 scalar_t__ dlm_query_join_proto_check (char*,int,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  o2hb_check_node_heartbeating_no_sem (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_query_join_handler(struct o2net_msg *msg, u32 len, void *data,
				  void **ret_data)
{
	struct dlm_query_join_request *query;
	struct dlm_query_join_packet packet = {
		.code = JOIN_DISALLOW,
	};
	struct dlm_ctxt *dlm = NULL;
	u32 response;
	u8 nodenum;

	query = (struct dlm_query_join_request *) msg->buf;

	mlog(0, "node %u wants to join domain %s\n", query->node_idx,
		  query->domain);

	/*
	 * If heartbeat doesn't consider the node live, tell it
	 * to back off and try again.  This gives heartbeat a chance
	 * to catch up.
	 */
	if (!o2hb_check_node_heartbeating_no_sem(query->node_idx)) {
		mlog(0, "node %u is not in our live map yet\n",
		     query->node_idx);

		packet.code = JOIN_DISALLOW;
		goto respond;
	}

	packet.code = JOIN_OK_NO_MAP;

	spin_lock(&dlm_domain_lock);
	dlm = __dlm_lookup_domain_full(query->domain, query->name_len);
	if (!dlm)
		goto unlock_respond;

	/*
	 * There is a small window where the joining node may not see the
	 * node(s) that just left but still part of the cluster. DISALLOW
	 * join request if joining node has different node map.
	 */
	nodenum=0;
	while (nodenum < O2NM_MAX_NODES) {
		if (test_bit(nodenum, dlm->domain_map)) {
			if (!byte_test_bit(nodenum, query->node_map)) {
				mlog(0, "disallow join as node %u does not "
				     "have node %u in its nodemap\n",
				     query->node_idx, nodenum);
				packet.code = JOIN_DISALLOW;
				goto unlock_respond;
			}
		}
		nodenum++;
	}

	/* Once the dlm ctxt is marked as leaving then we don't want
	 * to be put in someone's domain map.
	 * Also, explicitly disallow joining at certain troublesome
	 * times (ie. during recovery). */
	if (dlm->dlm_state != DLM_CTXT_LEAVING) {
		int bit = query->node_idx;
		spin_lock(&dlm->spinlock);

		if (dlm->dlm_state == DLM_CTXT_NEW &&
		    dlm->joining_node == DLM_LOCK_RES_OWNER_UNKNOWN) {
			/*If this is a brand new context and we
			 * haven't started our join process yet, then
			 * the other node won the race. */
			packet.code = JOIN_OK_NO_MAP;
		} else if (dlm->joining_node != DLM_LOCK_RES_OWNER_UNKNOWN) {
			/* Disallow parallel joins. */
			packet.code = JOIN_DISALLOW;
		} else if (dlm->reco.state & DLM_RECO_STATE_ACTIVE) {
			mlog(0, "node %u trying to join, but recovery "
			     "is ongoing.\n", bit);
			packet.code = JOIN_DISALLOW;
		} else if (test_bit(bit, dlm->recovery_map)) {
			mlog(0, "node %u trying to join, but it "
			     "still needs recovery.\n", bit);
			packet.code = JOIN_DISALLOW;
		} else if (test_bit(bit, dlm->domain_map)) {
			mlog(0, "node %u trying to join, but it "
			     "is still in the domain! needs recovery?\n",
			     bit);
			packet.code = JOIN_DISALLOW;
		} else {
			/* Alright we're fully a part of this domain
			 * so we keep some state as to who's joining
			 * and indicate to him that needs to be fixed
			 * up. */

			/* Make sure we speak compatible locking protocols.  */
			if (dlm_query_join_proto_check("DLM", bit,
						       &dlm->dlm_locking_proto,
						       &query->dlm_proto)) {
				packet.code = JOIN_PROTOCOL_MISMATCH;
			} else if (dlm_query_join_proto_check("fs", bit,
							      &dlm->fs_locking_proto,
							      &query->fs_proto)) {
				packet.code = JOIN_PROTOCOL_MISMATCH;
			} else {
				packet.dlm_minor = query->dlm_proto.pv_minor;
				packet.fs_minor = query->fs_proto.pv_minor;
				packet.code = JOIN_OK;
				__dlm_set_joining_node(dlm, query->node_idx);
			}
		}

		spin_unlock(&dlm->spinlock);
	}
unlock_respond:
	spin_unlock(&dlm_domain_lock);

respond:
	mlog(0, "We respond with %u\n", packet.code);

	dlm_query_join_packet_to_wire(&packet, &response);
	return response;
}