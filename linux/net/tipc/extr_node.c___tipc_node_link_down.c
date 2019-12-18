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
struct tipc_node {int* active_links; struct tipc_link_entry* links; scalar_t__ sync_point; int /*<<< orphan*/  net; int /*<<< orphan*/  addr; int /*<<< orphan*/  link_id; int /*<<< orphan*/  action_flags; int /*<<< orphan*/  working_links; } ;
struct tipc_media_addr {int dummy; } ;
struct tipc_link_entry {struct tipc_media_addr maddr; struct tipc_link* link; int /*<<< orphan*/  inputq; } ;
struct tipc_link {int dummy; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILOVER_MSG ; 
 int INVALID_BEARER_ID ; 
 int /*<<< orphan*/  LINK_FAILOVER_BEGIN_EVT ; 
 int /*<<< orphan*/  LINK_RESET_EVT ; 
 int /*<<< orphan*/  LINK_SYNCH_END_EVT ; 
 int MAX_BEARERS ; 
 int /*<<< orphan*/  NODE_FAILOVER_BEGIN_EVT ; 
 int /*<<< orphan*/  NODE_SYNCH_END_EVT ; 
 int /*<<< orphan*/  PEER_LOST_CONTACT_EVT ; 
 int /*<<< orphan*/  SELF_LOST_CONTACT_EVT ; 
 int /*<<< orphan*/  TIPC_DUMP_ALL ; 
 int /*<<< orphan*/  TIPC_NOTIFY_LINK_DOWN ; 
 int U16_MAX ; 
 int /*<<< orphan*/  node_is_up (struct tipc_node*) ; 
 int /*<<< orphan*/  node_lost_contact (struct tipc_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_bcast_dec_bearer_dst_cnt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tipc_bearer_remove_dest (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_link_build_reset_msg (struct tipc_link*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_fsm_evt (struct tipc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_link_id (struct tipc_link*) ; 
 scalar_t__ tipc_link_is_reset (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_link_is_up (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_link_name (struct tipc_link*) ; 
 scalar_t__ tipc_link_peer_is_down (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_link_plane (struct tipc_link*) ; 
 int tipc_link_prio (struct tipc_link*) ; 
 scalar_t__ tipc_link_rcv_nxt (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_link_reset (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_link_tnl_prepare (struct tipc_link*,struct tipc_link*,int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_node_fsm_evt (struct tipc_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_tipc_link_reset (struct tipc_link*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void __tipc_node_link_down(struct tipc_node *n, int *bearer_id,
				  struct sk_buff_head *xmitq,
				  struct tipc_media_addr **maddr)
{
	struct tipc_link_entry *le = &n->links[*bearer_id];
	int *slot0 = &n->active_links[0];
	int *slot1 = &n->active_links[1];
	int i, highest = 0, prio;
	struct tipc_link *l, *_l, *tnl;

	l = n->links[*bearer_id].link;
	if (!l || tipc_link_is_reset(l))
		return;

	n->working_links--;
	n->action_flags |= TIPC_NOTIFY_LINK_DOWN;
	n->link_id = tipc_link_id(l);

	tipc_bearer_remove_dest(n->net, *bearer_id, n->addr);

	pr_debug("Lost link <%s> on network plane %c\n",
		 tipc_link_name(l), tipc_link_plane(l));

	/* Select new active link if any available */
	*slot0 = INVALID_BEARER_ID;
	*slot1 = INVALID_BEARER_ID;
	for (i = 0; i < MAX_BEARERS; i++) {
		_l = n->links[i].link;
		if (!_l || !tipc_link_is_up(_l))
			continue;
		if (_l == l)
			continue;
		prio = tipc_link_prio(_l);
		if (prio < highest)
			continue;
		if (prio > highest) {
			highest = prio;
			*slot0 = i;
			*slot1 = i;
			continue;
		}
		*slot1 = i;
	}

	if (!node_is_up(n)) {
		if (tipc_link_peer_is_down(l))
			tipc_node_fsm_evt(n, PEER_LOST_CONTACT_EVT);
		tipc_node_fsm_evt(n, SELF_LOST_CONTACT_EVT);
		trace_tipc_link_reset(l, TIPC_DUMP_ALL, "link down!");
		tipc_link_fsm_evt(l, LINK_RESET_EVT);
		tipc_link_reset(l);
		tipc_link_build_reset_msg(l, xmitq);
		*maddr = &n->links[*bearer_id].maddr;
		node_lost_contact(n, &le->inputq);
		tipc_bcast_dec_bearer_dst_cnt(n->net, *bearer_id);
		return;
	}
	tipc_bcast_dec_bearer_dst_cnt(n->net, *bearer_id);

	/* There is still a working link => initiate failover */
	*bearer_id = n->active_links[0];
	tnl = n->links[*bearer_id].link;
	tipc_link_fsm_evt(tnl, LINK_SYNCH_END_EVT);
	tipc_node_fsm_evt(n, NODE_SYNCH_END_EVT);
	n->sync_point = tipc_link_rcv_nxt(tnl) + (U16_MAX / 2 - 1);
	tipc_link_tnl_prepare(l, tnl, FAILOVER_MSG, xmitq);
	trace_tipc_link_reset(l, TIPC_DUMP_ALL, "link down -> failover!");
	tipc_link_reset(l);
	tipc_link_fsm_evt(l, LINK_RESET_EVT);
	tipc_link_fsm_evt(l, LINK_FAILOVER_BEGIN_EVT);
	tipc_node_fsm_evt(n, NODE_FAILOVER_BEGIN_EVT);
	*maddr = &n->links[*bearer_id].maddr;
}