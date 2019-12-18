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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct tipc_msg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  recv_nacks; } ;
struct tipc_link {int /*<<< orphan*/  nack_state; int /*<<< orphan*/  rcv_nxt; TYPE_1__ stats; int /*<<< orphan*/  bc_sndlink; int /*<<< orphan*/  net; int /*<<< orphan*/  bc_peer_is_up; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_NACK_SND_SUPPRESS ; 
 int STATE_MSG ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  less (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ more (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ msg_bcast_ack (struct tipc_msg*) ; 
 scalar_t__ msg_bcgap_to (struct tipc_msg*) ; 
 scalar_t__ msg_destnode (struct tipc_msg*) ; 
 int msg_type (struct tipc_msg*) ; 
 int /*<<< orphan*/  tipc_link_bc_ack_rcv (struct tipc_link*,scalar_t__,struct sk_buff_head*) ; 
 int tipc_link_bc_retrans (int /*<<< orphan*/ ,struct tipc_link*,scalar_t__,scalar_t__,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_is_up (struct tipc_link*) ; 
 scalar_t__ tipc_own_addr (int /*<<< orphan*/ ) ; 

int tipc_link_bc_nack_rcv(struct tipc_link *l, struct sk_buff *skb,
			  struct sk_buff_head *xmitq)
{
	struct tipc_msg *hdr = buf_msg(skb);
	u32 dnode = msg_destnode(hdr);
	int mtyp = msg_type(hdr);
	u16 acked = msg_bcast_ack(hdr);
	u16 from = acked + 1;
	u16 to = msg_bcgap_to(hdr);
	u16 peers_snd_nxt = to + 1;
	int rc = 0;

	kfree_skb(skb);

	if (!tipc_link_is_up(l) || !l->bc_peer_is_up)
		return 0;

	if (mtyp != STATE_MSG)
		return 0;

	if (dnode == tipc_own_addr(l->net)) {
		tipc_link_bc_ack_rcv(l, acked, xmitq);
		rc = tipc_link_bc_retrans(l->bc_sndlink, l, from, to, xmitq);
		l->stats.recv_nacks++;
		return rc;
	}

	/* Msg for other node => suppress own NACK at next sync if applicable */
	if (more(peers_snd_nxt, l->rcv_nxt) && !less(l->rcv_nxt, from))
		l->nack_state = BC_NACK_SND_SUPPRESS;

	return 0;
}