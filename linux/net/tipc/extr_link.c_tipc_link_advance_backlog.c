#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct tipc_msg {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  sent_pkts; } ;
struct sk_buff_head {int dummy; } ;
struct tipc_link {scalar_t__ window; scalar_t__ snd_nxt; TYPE_3__ stats; scalar_t__ rcv_unacked; int /*<<< orphan*/  ackers; struct sk_buff_head transmq; TYPE_2__* backlog; int /*<<< orphan*/  backlogq; TYPE_1__* bc_rcvlink; scalar_t__ rcv_nxt; } ;
struct sk_buff {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  ackers; int /*<<< orphan*/  nxt_retr; } ;
struct TYPE_6__ {struct sk_buff* target_bskb; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {scalar_t__ rcv_nxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TIPC_BC_RETR_LIM ; 
 TYPE_4__* TIPC_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 scalar_t__ link_is_bc_sndlink (struct tipc_link*) ; 
 size_t msg_importance (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_ack (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_bcast_ack (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_seqno (struct tipc_msg*,scalar_t__) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (struct sk_buff_head*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void tipc_link_advance_backlog(struct tipc_link *l,
				      struct sk_buff_head *xmitq)
{
	struct sk_buff *skb, *_skb;
	struct tipc_msg *hdr;
	u16 seqno = l->snd_nxt;
	u16 ack = l->rcv_nxt - 1;
	u16 bc_ack = l->bc_rcvlink->rcv_nxt - 1;
	u32 imp;

	while (skb_queue_len(&l->transmq) < l->window) {
		skb = skb_peek(&l->backlogq);
		if (!skb)
			break;
		_skb = skb_clone(skb, GFP_ATOMIC);
		if (!_skb)
			break;
		__skb_dequeue(&l->backlogq);
		hdr = buf_msg(skb);
		imp = msg_importance(hdr);
		l->backlog[imp].len--;
		if (unlikely(skb == l->backlog[imp].target_bskb))
			l->backlog[imp].target_bskb = NULL;
		__skb_queue_tail(&l->transmq, skb);
		/* next retransmit attempt */
		if (link_is_bc_sndlink(l))
			TIPC_SKB_CB(skb)->nxt_retr = TIPC_BC_RETR_LIM;

		__skb_queue_tail(xmitq, _skb);
		TIPC_SKB_CB(skb)->ackers = l->ackers;
		msg_set_seqno(hdr, seqno);
		msg_set_ack(hdr, ack);
		msg_set_bcast_ack(hdr, bc_ack);
		l->rcv_unacked = 0;
		l->stats.sent_pkts++;
		seqno++;
	}
	l->snd_nxt = seqno;
}