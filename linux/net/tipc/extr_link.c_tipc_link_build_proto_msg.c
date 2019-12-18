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
typedef  int u16 ;
struct tipc_msg {int dummy; } ;
struct tipc_mon_state {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sent_nacks; int /*<<< orphan*/  sent_probes; int /*<<< orphan*/  sent_states; } ;
struct sk_buff_head {int dummy; } ;
struct tipc_link {int rcv_nxt; int peer_caps; int /*<<< orphan*/  name; TYPE_2__ stats; int /*<<< orphan*/  if_name; int /*<<< orphan*/  advertised_mtu; int /*<<< orphan*/  peer_session; scalar_t__ rcv_unacked; int /*<<< orphan*/  bearer_id; int /*<<< orphan*/  net; int /*<<< orphan*/  snd_nxt_state; scalar_t__ snd_nxt; TYPE_1__* bc_sndlink; int /*<<< orphan*/  net_plane; int /*<<< orphan*/  session; int /*<<< orphan*/  addr; struct tipc_mon_state mon_state; struct sk_buff_head deferdq; struct tipc_link* bc_rcvlink; } ;
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct TYPE_3__ {scalar_t__ snd_nxt; } ;

/* Variables and functions */
 int ACTIVATE_MSG ; 
 int INT_H_SIZE ; 
 int /*<<< orphan*/  LINK_PROTOCOL ; 
 scalar_t__ MAX_GAP_ACK_BLKS_SZ ; 
 int STATE_MSG ; 
 int /*<<< orphan*/  TC_PRIO_CONTROL ; 
 int TIPC_GAP_ACK_BLOCK ; 
 int TIPC_LINK_PROTO_SEQNO ; 
 int TIPC_MAX_IF_NAME ; 
 int U16_MAX ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int buf_seqno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_bc_rcv_gap (struct tipc_link*) ; 
 int link_is_up (struct tipc_link*) ; 
 void* msg_data (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_ack (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_bc_ack_invalid (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_bc_gap (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_bcast_ack (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_bearer_id (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_dest_session (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_dest_session_valid (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_is_keepalive (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_last_bcast (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_link_tolerance (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_linkprio (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_max_pkt (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_net_plane (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_next_sent (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_probe (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_redundant_link (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_seq_gap (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_seqno (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_session (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  skb_peek (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 int /*<<< orphan*/  strcpy (void*,int /*<<< orphan*/ ) ; 
 int tipc_build_gap_ack_blks (struct tipc_link*,void*) ; 
 scalar_t__ tipc_link_is_blocked (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_link_is_up (struct tipc_link*) ; 
 scalar_t__ tipc_max_domain_size ; 
 int /*<<< orphan*/  tipc_mon_prep (int /*<<< orphan*/ ,void*,int*,struct tipc_mon_state*,int /*<<< orphan*/ ) ; 
 struct sk_buff* tipc_msg_create (int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_own_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_tipc_proto_build (struct sk_buff*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tipc_link_build_proto_msg(struct tipc_link *l, int mtyp, bool probe,
				      bool probe_reply, u16 rcvgap,
				      int tolerance, int priority,
				      struct sk_buff_head *xmitq)
{
	struct tipc_link *bcl = l->bc_rcvlink;
	struct sk_buff *skb;
	struct tipc_msg *hdr;
	struct sk_buff_head *dfq = &l->deferdq;
	bool node_up = link_is_up(bcl);
	struct tipc_mon_state *mstate = &l->mon_state;
	int dlen = 0;
	void *data;
	u16 glen = 0;

	/* Don't send protocol message during reset or link failover */
	if (tipc_link_is_blocked(l))
		return;

	if (!tipc_link_is_up(l) && (mtyp == STATE_MSG))
		return;

	if (!skb_queue_empty(dfq))
		rcvgap = buf_seqno(skb_peek(dfq)) - l->rcv_nxt;

	skb = tipc_msg_create(LINK_PROTOCOL, mtyp, INT_H_SIZE,
			      tipc_max_domain_size + MAX_GAP_ACK_BLKS_SZ,
			      l->addr, tipc_own_addr(l->net), 0, 0, 0);
	if (!skb)
		return;

	hdr = buf_msg(skb);
	data = msg_data(hdr);
	msg_set_session(hdr, l->session);
	msg_set_bearer_id(hdr, l->bearer_id);
	msg_set_net_plane(hdr, l->net_plane);
	msg_set_next_sent(hdr, l->snd_nxt);
	msg_set_ack(hdr, l->rcv_nxt - 1);
	msg_set_bcast_ack(hdr, bcl->rcv_nxt - 1);
	msg_set_bc_ack_invalid(hdr, !node_up);
	msg_set_last_bcast(hdr, l->bc_sndlink->snd_nxt - 1);
	msg_set_link_tolerance(hdr, tolerance);
	msg_set_linkprio(hdr, priority);
	msg_set_redundant_link(hdr, node_up);
	msg_set_seq_gap(hdr, 0);
	msg_set_seqno(hdr, l->snd_nxt + U16_MAX / 2);

	if (mtyp == STATE_MSG) {
		if (l->peer_caps & TIPC_LINK_PROTO_SEQNO)
			msg_set_seqno(hdr, l->snd_nxt_state++);
		msg_set_seq_gap(hdr, rcvgap);
		msg_set_bc_gap(hdr, link_bc_rcv_gap(bcl));
		msg_set_probe(hdr, probe);
		msg_set_is_keepalive(hdr, probe || probe_reply);
		if (l->peer_caps & TIPC_GAP_ACK_BLOCK)
			glen = tipc_build_gap_ack_blks(l, data);
		tipc_mon_prep(l->net, data + glen, &dlen, mstate, l->bearer_id);
		msg_set_size(hdr, INT_H_SIZE + glen + dlen);
		skb_trim(skb, INT_H_SIZE + glen + dlen);
		l->stats.sent_states++;
		l->rcv_unacked = 0;
	} else {
		/* RESET_MSG or ACTIVATE_MSG */
		if (mtyp == ACTIVATE_MSG) {
			msg_set_dest_session_valid(hdr, 1);
			msg_set_dest_session(hdr, l->peer_session);
		}
		msg_set_max_pkt(hdr, l->advertised_mtu);
		strcpy(data, l->if_name);
		msg_set_size(hdr, INT_H_SIZE + TIPC_MAX_IF_NAME);
		skb_trim(skb, INT_H_SIZE + TIPC_MAX_IF_NAME);
	}
	if (probe)
		l->stats.sent_probes++;
	if (rcvgap)
		l->stats.sent_nacks++;
	skb->priority = TC_PRIO_CONTROL;
	__skb_queue_tail(xmitq, skb);
	trace_tipc_proto_build(skb, false, l->name);
}