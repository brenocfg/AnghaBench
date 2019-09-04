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
struct tcp_sock {scalar_t__ rcv_nxt; int syn_data_acked; int /*<<< orphan*/  bytes_received; scalar_t__ segs_in; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  truesize; } ;
struct TYPE_2__ {scalar_t__ end_seq; int tcp_flags; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int TCPHDR_FIN ; 
 int TCPHDR_SYN ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  sk_forced_mem_schedule (struct sock*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  tcp_fin (struct sock*) ; 
 int /*<<< orphan*/  tcp_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_segs_in (struct tcp_sock*,struct sk_buff*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

void tcp_fastopen_add_skb(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (TCP_SKB_CB(skb)->end_seq == tp->rcv_nxt)
		return;

	skb = skb_clone(skb, GFP_ATOMIC);
	if (!skb)
		return;

	skb_dst_drop(skb);
	/* segs_in has been initialized to 1 in tcp_create_openreq_child().
	 * Hence, reset segs_in to 0 before calling tcp_segs_in()
	 * to avoid double counting.  Also, tcp_segs_in() expects
	 * skb->len to include the tcp_hdrlen.  Hence, it should
	 * be called before __skb_pull().
	 */
	tp->segs_in = 0;
	tcp_segs_in(tp, skb);
	__skb_pull(skb, tcp_hdrlen(skb));
	sk_forced_mem_schedule(sk, skb->truesize);
	skb_set_owner_r(skb, sk);

	TCP_SKB_CB(skb)->seq++;
	TCP_SKB_CB(skb)->tcp_flags &= ~TCPHDR_SYN;

	tp->rcv_nxt = TCP_SKB_CB(skb)->end_seq;
	__skb_queue_tail(&sk->sk_receive_queue, skb);
	tp->syn_data_acked = 1;

	/* u64_stats_update_begin(&tp->syncp) not needed here,
	 * as we certainly are not changing upper 32bit value (0)
	 */
	tp->bytes_received = skb->len;

	if (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN)
		tcp_fin(sk);
}