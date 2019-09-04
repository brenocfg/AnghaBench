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
typedef  scalar_t__ u16 ;
struct tipc_msg {int dummy; } ;
struct TYPE_6__ {int sent_fragments; int /*<<< orphan*/  sent_bundles; int /*<<< orphan*/  sent_bundled; int /*<<< orphan*/  sent_pkts; int /*<<< orphan*/  sent_fragmented; } ;
struct sk_buff_head {int dummy; } ;
struct tipc_link {unsigned int window; unsigned int mtu; scalar_t__ snd_nxt; TYPE_3__* backlog; TYPE_2__ stats; int /*<<< orphan*/  addr; scalar_t__ rcv_unacked; int /*<<< orphan*/  ackers; int /*<<< orphan*/  name; struct sk_buff_head backlogq; struct sk_buff_head transmq; TYPE_1__* bc_rcvlink; scalar_t__ rcv_nxt; } ;
struct sk_buff {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  ackers; } ;
struct TYPE_7__ {scalar_t__ len; scalar_t__ limit; } ;
struct TYPE_5__ {scalar_t__ rcv_nxt; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_4__* TIPC_SKB_CB (struct sk_buff*) ; 
 int TIPC_SYSTEM_IMPORTANCE ; 
 int /*<<< orphan*/  __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  link_rst_msg ; 
 int link_schedule_user (struct tipc_link*,struct tipc_msg*) ; 
 size_t msg_importance (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_ack (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_bcast_ack (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_seqno (struct tipc_msg*,scalar_t__) ; 
 unsigned int msg_size (struct tipc_msg*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_peek_tail (struct sk_buff_head*) ; 
 unsigned int skb_queue_len (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_splice_tail_init (struct sk_buff_head*,struct sk_buff_head*) ; 
 scalar_t__ tipc_msg_bundle (int /*<<< orphan*/ ,struct tipc_msg*,unsigned int) ; 
 scalar_t__ tipc_msg_make_bundle (struct sk_buff**,struct tipc_msg*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int tipc_link_xmit(struct tipc_link *l, struct sk_buff_head *list,
		   struct sk_buff_head *xmitq)
{
	struct tipc_msg *hdr = buf_msg(skb_peek(list));
	unsigned int maxwin = l->window;
	int imp = msg_importance(hdr);
	unsigned int mtu = l->mtu;
	u16 ack = l->rcv_nxt - 1;
	u16 seqno = l->snd_nxt;
	u16 bc_ack = l->bc_rcvlink->rcv_nxt - 1;
	struct sk_buff_head *transmq = &l->transmq;
	struct sk_buff_head *backlogq = &l->backlogq;
	struct sk_buff *skb, *_skb, *bskb;
	int pkt_cnt = skb_queue_len(list);
	int rc = 0;

	if (unlikely(msg_size(hdr) > mtu)) {
		skb_queue_purge(list);
		return -EMSGSIZE;
	}

	/* Allow oversubscription of one data msg per source at congestion */
	if (unlikely(l->backlog[imp].len >= l->backlog[imp].limit)) {
		if (imp == TIPC_SYSTEM_IMPORTANCE) {
			pr_warn("%s<%s>, link overflow", link_rst_msg, l->name);
			return -ENOBUFS;
		}
		rc = link_schedule_user(l, hdr);
	}

	if (pkt_cnt > 1) {
		l->stats.sent_fragmented++;
		l->stats.sent_fragments += pkt_cnt;
	}

	/* Prepare each packet for sending, and add to relevant queue: */
	while (skb_queue_len(list)) {
		skb = skb_peek(list);
		hdr = buf_msg(skb);
		msg_set_seqno(hdr, seqno);
		msg_set_ack(hdr, ack);
		msg_set_bcast_ack(hdr, bc_ack);

		if (likely(skb_queue_len(transmq) < maxwin)) {
			_skb = skb_clone(skb, GFP_ATOMIC);
			if (!_skb) {
				skb_queue_purge(list);
				return -ENOBUFS;
			}
			__skb_dequeue(list);
			__skb_queue_tail(transmq, skb);
			__skb_queue_tail(xmitq, _skb);
			TIPC_SKB_CB(skb)->ackers = l->ackers;
			l->rcv_unacked = 0;
			l->stats.sent_pkts++;
			seqno++;
			continue;
		}
		if (tipc_msg_bundle(skb_peek_tail(backlogq), hdr, mtu)) {
			kfree_skb(__skb_dequeue(list));
			l->stats.sent_bundled++;
			continue;
		}
		if (tipc_msg_make_bundle(&bskb, hdr, mtu, l->addr)) {
			kfree_skb(__skb_dequeue(list));
			__skb_queue_tail(backlogq, bskb);
			l->backlog[msg_importance(buf_msg(bskb))].len++;
			l->stats.sent_bundled++;
			l->stats.sent_bundles++;
			continue;
		}
		l->backlog[imp].len += skb_queue_len(list);
		skb_queue_splice_tail_init(list, backlogq);
	}
	l->snd_nxt = seqno;
	return rc;
}