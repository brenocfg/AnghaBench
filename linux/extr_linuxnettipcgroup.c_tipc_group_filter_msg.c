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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct tipc_member {int /*<<< orphan*/  state; int /*<<< orphan*/  bc_rcv_nxt; struct sk_buff_head deferredq; int /*<<< orphan*/  instance; } ;
struct tipc_group {int /*<<< orphan*/  events; int /*<<< orphan*/  instance; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  orig_member; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRP_ACK_MSG ; 
 int /*<<< orphan*/  MBR_LEAVING ; 
#define  TIPC_GRP_BCAST_MSG 131 
#define  TIPC_GRP_MCAST_MSG 130 
#define  TIPC_GRP_MEMBER_EVT 129 
#define  TIPC_GRP_UCAST_MSG 128 
 TYPE_1__* TIPC_SKB_CB (struct sk_buff*) ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ more (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msg_blocks (struct tipc_msg*) ; 
 int msg_grp_bc_ack_req (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_grp_bc_seqno (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_in_group (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_nameinst (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_orignode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_origport (struct tipc_msg*) ; 
 int msg_type (struct tipc_msg*) ; 
 struct sk_buff* skb_peek (struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_group_delete_member (struct tipc_group*,struct tipc_member*) ; 
 struct tipc_member* tipc_group_find_member (struct tipc_group*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_group_is_sender (struct tipc_member*) ; 
 int /*<<< orphan*/  tipc_group_proto_xmit (struct tipc_group*,struct tipc_member*,int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_group_sort_msg (struct sk_buff*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_group_update_rcv_win (struct tipc_group*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff_head*) ; 

void tipc_group_filter_msg(struct tipc_group *grp, struct sk_buff_head *inputq,
			   struct sk_buff_head *xmitq)
{
	struct sk_buff *skb = __skb_dequeue(inputq);
	bool ack, deliver, update, leave = false;
	struct sk_buff_head *defq;
	struct tipc_member *m;
	struct tipc_msg *hdr;
	u32 node, port;
	int mtyp, blks;

	if (!skb)
		return;

	hdr = buf_msg(skb);
	node =  msg_orignode(hdr);
	port = msg_origport(hdr);

	if (!msg_in_group(hdr))
		goto drop;

	m = tipc_group_find_member(grp, node, port);
	if (!tipc_group_is_sender(m))
		goto drop;

	if (less(msg_grp_bc_seqno(hdr), m->bc_rcv_nxt))
		goto drop;

	TIPC_SKB_CB(skb)->orig_member = m->instance;
	defq = &m->deferredq;
	tipc_group_sort_msg(skb, defq);

	while ((skb = skb_peek(defq))) {
		hdr = buf_msg(skb);
		mtyp = msg_type(hdr);
		blks = msg_blocks(hdr);
		deliver = true;
		ack = false;
		update = false;

		if (more(msg_grp_bc_seqno(hdr), m->bc_rcv_nxt))
			break;

		/* Decide what to do with message */
		switch (mtyp) {
		case TIPC_GRP_MCAST_MSG:
			if (msg_nameinst(hdr) != grp->instance) {
				update = true;
				deliver = false;
			}
			/* Fall thru */
		case TIPC_GRP_BCAST_MSG:
			m->bc_rcv_nxt++;
			ack = msg_grp_bc_ack_req(hdr);
			break;
		case TIPC_GRP_UCAST_MSG:
			break;
		case TIPC_GRP_MEMBER_EVT:
			if (m->state == MBR_LEAVING)
				leave = true;
			if (!grp->events)
				deliver = false;
			break;
		default:
			break;
		}

		/* Execute decisions */
		__skb_dequeue(defq);
		if (deliver)
			__skb_queue_tail(inputq, skb);
		else
			kfree_skb(skb);

		if (ack)
			tipc_group_proto_xmit(grp, m, GRP_ACK_MSG, xmitq);

		if (leave) {
			__skb_queue_purge(defq);
			tipc_group_delete_member(grp, m);
			break;
		}
		if (!update)
			continue;

		tipc_group_update_rcv_win(grp, blks, node, port, xmitq);
	}
	return;
drop:
	kfree_skb(skb);
}