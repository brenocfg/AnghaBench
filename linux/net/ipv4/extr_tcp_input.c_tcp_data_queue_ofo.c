#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_12__ {struct rb_node* rb_node; } ;
struct TYPE_9__ {int num_sacks; } ;
struct tcp_sock {struct sk_buff* ooo_last_skb; TYPE_4__ out_of_order_queue; TYPE_2__* selective_acks; TYPE_1__ rx_opt; int /*<<< orphan*/  rcv_ooopack; scalar_t__ pred_flags; } ;
struct sock {int dummy; } ;
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct sk_buff {struct rb_node rbnode; int /*<<< orphan*/  truesize; } ;
struct TYPE_13__ {void* seq; void* end_seq; } ;
struct TYPE_11__ {int /*<<< orphan*/  gso_segs; } ;
struct TYPE_10__ {void* end_seq; void* start_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPOFODROP ; 
 int /*<<< orphan*/  LINUX_MIB_TCPOFOMERGE ; 
 int /*<<< orphan*/  LINUX_MIB_TCPOFOQUEUE ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RB_EMPTY_ROOT (TYPE_4__*) ; 
 TYPE_7__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ after (void*,void*) ; 
 scalar_t__ before (void*,void*) ; 
 int /*<<< orphan*/  inet_csk_schedule_ack (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb_partial (struct sk_buff*,int) ; 
 scalar_t__ max_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (struct rb_node*,TYPE_4__*) ; 
 int /*<<< orphan*/  rb_insert_color (struct rb_node*,TYPE_4__*) ; 
 int /*<<< orphan*/  rb_link_node (struct rb_node*,struct rb_node*,struct rb_node**) ; 
 int /*<<< orphan*/  rb_replace_node (struct rb_node*,struct rb_node*,TYPE_4__*) ; 
 struct sk_buff* rb_to_skb (struct rb_node*) ; 
 int /*<<< orphan*/  skb_condense (struct sk_buff*) ; 
 struct sk_buff* skb_rb_next (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_drop (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_dsack_extend (struct sock*,void*,void*) ; 
 int /*<<< orphan*/  tcp_dsack_set (struct sock*,void*,void*) ; 
 int /*<<< orphan*/  tcp_ecn_check_ce (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_grow_window (struct sock*,struct sk_buff*) ; 
 scalar_t__ tcp_is_sack (struct tcp_sock*) ; 
 scalar_t__ tcp_ooo_try_coalesce (struct sock*,struct sk_buff*,struct sk_buff*,int*) ; 
 int /*<<< orphan*/  tcp_sack_new_ofo_skb (struct sock*,void*,void*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_try_rmem_schedule (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u16 ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_data_queue_ofo(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct rb_node **p, *parent;
	struct sk_buff *skb1;
	u32 seq, end_seq;
	bool fragstolen;

	tcp_ecn_check_ce(sk, skb);

	if (unlikely(tcp_try_rmem_schedule(sk, skb, skb->truesize))) {
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPOFODROP);
		tcp_drop(sk, skb);
		return;
	}

	/* Disable header prediction. */
	tp->pred_flags = 0;
	inet_csk_schedule_ack(sk);

	tp->rcv_ooopack += max_t(u16, 1, skb_shinfo(skb)->gso_segs);
	NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPOFOQUEUE);
	seq = TCP_SKB_CB(skb)->seq;
	end_seq = TCP_SKB_CB(skb)->end_seq;

	p = &tp->out_of_order_queue.rb_node;
	if (RB_EMPTY_ROOT(&tp->out_of_order_queue)) {
		/* Initial out of order segment, build 1 SACK. */
		if (tcp_is_sack(tp)) {
			tp->rx_opt.num_sacks = 1;
			tp->selective_acks[0].start_seq = seq;
			tp->selective_acks[0].end_seq = end_seq;
		}
		rb_link_node(&skb->rbnode, NULL, p);
		rb_insert_color(&skb->rbnode, &tp->out_of_order_queue);
		tp->ooo_last_skb = skb;
		goto end;
	}

	/* In the typical case, we are adding an skb to the end of the list.
	 * Use of ooo_last_skb avoids the O(Log(N)) rbtree lookup.
	 */
	if (tcp_ooo_try_coalesce(sk, tp->ooo_last_skb,
				 skb, &fragstolen)) {
coalesce_done:
		tcp_grow_window(sk, skb);
		kfree_skb_partial(skb, fragstolen);
		skb = NULL;
		goto add_sack;
	}
	/* Can avoid an rbtree lookup if we are adding skb after ooo_last_skb */
	if (!before(seq, TCP_SKB_CB(tp->ooo_last_skb)->end_seq)) {
		parent = &tp->ooo_last_skb->rbnode;
		p = &parent->rb_right;
		goto insert;
	}

	/* Find place to insert this segment. Handle overlaps on the way. */
	parent = NULL;
	while (*p) {
		parent = *p;
		skb1 = rb_to_skb(parent);
		if (before(seq, TCP_SKB_CB(skb1)->seq)) {
			p = &parent->rb_left;
			continue;
		}
		if (before(seq, TCP_SKB_CB(skb1)->end_seq)) {
			if (!after(end_seq, TCP_SKB_CB(skb1)->end_seq)) {
				/* All the bits are present. Drop. */
				NET_INC_STATS(sock_net(sk),
					      LINUX_MIB_TCPOFOMERGE);
				tcp_drop(sk, skb);
				skb = NULL;
				tcp_dsack_set(sk, seq, end_seq);
				goto add_sack;
			}
			if (after(seq, TCP_SKB_CB(skb1)->seq)) {
				/* Partial overlap. */
				tcp_dsack_set(sk, seq, TCP_SKB_CB(skb1)->end_seq);
			} else {
				/* skb's seq == skb1's seq and skb covers skb1.
				 * Replace skb1 with skb.
				 */
				rb_replace_node(&skb1->rbnode, &skb->rbnode,
						&tp->out_of_order_queue);
				tcp_dsack_extend(sk,
						 TCP_SKB_CB(skb1)->seq,
						 TCP_SKB_CB(skb1)->end_seq);
				NET_INC_STATS(sock_net(sk),
					      LINUX_MIB_TCPOFOMERGE);
				tcp_drop(sk, skb1);
				goto merge_right;
			}
		} else if (tcp_ooo_try_coalesce(sk, skb1,
						skb, &fragstolen)) {
			goto coalesce_done;
		}
		p = &parent->rb_right;
	}
insert:
	/* Insert segment into RB tree. */
	rb_link_node(&skb->rbnode, parent, p);
	rb_insert_color(&skb->rbnode, &tp->out_of_order_queue);

merge_right:
	/* Remove other segments covered by skb. */
	while ((skb1 = skb_rb_next(skb)) != NULL) {
		if (!after(end_seq, TCP_SKB_CB(skb1)->seq))
			break;
		if (before(end_seq, TCP_SKB_CB(skb1)->end_seq)) {
			tcp_dsack_extend(sk, TCP_SKB_CB(skb1)->seq,
					 end_seq);
			break;
		}
		rb_erase(&skb1->rbnode, &tp->out_of_order_queue);
		tcp_dsack_extend(sk, TCP_SKB_CB(skb1)->seq,
				 TCP_SKB_CB(skb1)->end_seq);
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPOFOMERGE);
		tcp_drop(sk, skb1);
	}
	/* If there is no skb after us, we are the last_skb ! */
	if (!skb1)
		tp->ooo_last_skb = skb;

add_sack:
	if (tcp_is_sack(tp))
		tcp_sack_new_ofo_skb(sk, seq, end_seq);
end:
	if (skb) {
		tcp_grow_window(sk, skb);
		skb_condense(skb);
		skb_set_owner_r(skb, sk);
	}
}