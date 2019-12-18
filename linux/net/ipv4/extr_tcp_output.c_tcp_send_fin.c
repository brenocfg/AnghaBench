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
struct tcp_sock {int /*<<< orphan*/  write_seq; scalar_t__ snd_nxt; } ;
struct sock {int /*<<< orphan*/  sk_allocation; int /*<<< orphan*/  tcp_rtx_queue; } ;
struct sk_buff {int /*<<< orphan*/  truesize; int /*<<< orphan*/  tcp_tsorted_anchor; } ;
struct TYPE_2__ {int tcp_flags; int /*<<< orphan*/  end_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_TCP_HEADER ; 
 int TCPHDR_ACK ; 
 int TCPHDR_FIN ; 
 int /*<<< orphan*/  TCP_NAGLE_OFF ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __tcp_push_pending_frames (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb_fclone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_forced_mem_schedule (struct sock*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_rb_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_current_mss (struct sock*) ; 
 int /*<<< orphan*/  tcp_init_nondata_skb (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_queue_skb (struct sock*,struct sk_buff*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_under_memory_pressure (struct sock*) ; 
 scalar_t__ tcp_write_queue_empty (struct sock*) ; 
 struct sk_buff* tcp_write_queue_tail (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

void tcp_send_fin(struct sock *sk)
{
	struct sk_buff *skb, *tskb = tcp_write_queue_tail(sk);
	struct tcp_sock *tp = tcp_sk(sk);

	/* Optimization, tack on the FIN if we have one skb in write queue and
	 * this skb was not yet sent, or we are under memory pressure.
	 * Note: in the latter case, FIN packet will be sent after a timeout,
	 * as TCP stack thinks it has already been transmitted.
	 */
	if (!tskb && tcp_under_memory_pressure(sk))
		tskb = skb_rb_last(&sk->tcp_rtx_queue);

	if (tskb) {
		TCP_SKB_CB(tskb)->tcp_flags |= TCPHDR_FIN;
		TCP_SKB_CB(tskb)->end_seq++;
		tp->write_seq++;
		if (tcp_write_queue_empty(sk)) {
			/* This means tskb was already sent.
			 * Pretend we included the FIN on previous transmit.
			 * We need to set tp->snd_nxt to the value it would have
			 * if FIN had been sent. This is because retransmit path
			 * does not change tp->snd_nxt.
			 */
			WRITE_ONCE(tp->snd_nxt, tp->snd_nxt + 1);
			return;
		}
	} else {
		skb = alloc_skb_fclone(MAX_TCP_HEADER, sk->sk_allocation);
		if (unlikely(!skb))
			return;

		INIT_LIST_HEAD(&skb->tcp_tsorted_anchor);
		skb_reserve(skb, MAX_TCP_HEADER);
		sk_forced_mem_schedule(sk, skb->truesize);
		/* FIN eats a sequence byte, write_seq advanced by tcp_queue_skb(). */
		tcp_init_nondata_skb(skb, tp->write_seq,
				     TCPHDR_ACK | TCPHDR_FIN);
		tcp_queue_skb(sk, skb);
	}
	__tcp_push_pending_frames(sk, tcp_current_mss(sk), TCP_NAGLE_OFF);
}