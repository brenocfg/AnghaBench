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
typedef  scalar_t__ u32 ;
struct sk_buff_head {int dummy; } ;
struct tipc_bclink_entry {struct sk_buff_head namedq; struct sk_buff_head inputq1; int /*<<< orphan*/  link; } ;
struct tipc_node {struct tipc_bclink_entry bc_entry; struct tipc_link_entry* links; } ;
struct tipc_msg {int dummy; } ;
struct tipc_link_entry {int /*<<< orphan*/  maddr; int /*<<< orphan*/  link; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int BCAST_PROTOCOL ; 
 int TIPC_LINK_DOWN_EVT ; 
 int TIPC_LINK_SND_STATE ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ msg_destnode (struct tipc_msg*) ; 
 scalar_t__ msg_prevnode (struct tipc_msg*) ; 
 int msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 int tipc_bcast_rcv (struct net*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_bearer_xmit (struct net*,int,struct sk_buff_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_link_build_state_msg (int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_named_rcv (struct net*,struct sk_buff_head*) ; 
 struct tipc_node* tipc_node_find (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  tipc_node_mcast_rcv (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_read_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_read_unlock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_reset_links (struct tipc_node*) ; 
 scalar_t__ tipc_own_addr (struct net*) ; 

__attribute__((used)) static void tipc_node_bc_rcv(struct net *net, struct sk_buff *skb, int bearer_id)
{
	int rc;
	struct sk_buff_head xmitq;
	struct tipc_bclink_entry *be;
	struct tipc_link_entry *le;
	struct tipc_msg *hdr = buf_msg(skb);
	int usr = msg_user(hdr);
	u32 dnode = msg_destnode(hdr);
	struct tipc_node *n;

	__skb_queue_head_init(&xmitq);

	/* If NACK for other node, let rcv link for that node peek into it */
	if ((usr == BCAST_PROTOCOL) && (dnode != tipc_own_addr(net)))
		n = tipc_node_find(net, dnode);
	else
		n = tipc_node_find(net, msg_prevnode(hdr));
	if (!n) {
		kfree_skb(skb);
		return;
	}
	be = &n->bc_entry;
	le = &n->links[bearer_id];

	rc = tipc_bcast_rcv(net, be->link, skb);

	/* Broadcast ACKs are sent on a unicast link */
	if (rc & TIPC_LINK_SND_STATE) {
		tipc_node_read_lock(n);
		tipc_link_build_state_msg(le->link, &xmitq);
		tipc_node_read_unlock(n);
	}

	if (!skb_queue_empty(&xmitq))
		tipc_bearer_xmit(net, bearer_id, &xmitq, &le->maddr);

	if (!skb_queue_empty(&be->inputq1))
		tipc_node_mcast_rcv(n);

	/* Handle NAME_DISTRIBUTOR messages sent from 1.7 nodes */
	if (!skb_queue_empty(&n->bc_entry.namedq))
		tipc_named_rcv(net, &n->bc_entry.namedq);

	/* If reassembly or retransmission failure => reset all links to peer */
	if (rc & TIPC_LINK_DOWN_EVT)
		tipc_node_reset_links(n);

	tipc_node_put(n);
}