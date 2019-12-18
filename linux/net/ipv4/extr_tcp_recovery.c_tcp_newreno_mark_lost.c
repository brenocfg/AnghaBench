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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct tcp_sock {scalar_t__ sacked_out; scalar_t__ reordering; } ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_4__ {int sacked; } ;
struct TYPE_3__ {scalar_t__ icsk_ca_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int TCPCB_LOST ; 
 scalar_t__ const TCP_CA_Recovery ; 
 int /*<<< orphan*/  TCP_FRAG_IN_RTX_QUEUE ; 
 TYPE_2__* TCP_SKB_CB (struct sk_buff*) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  tcp_fragment (struct sock*,int /*<<< orphan*/ ,struct sk_buff*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct sk_buff* tcp_rtx_queue_head (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_skb_mark_lost_uncond_verify (struct tcp_sock*,struct sk_buff*) ; 
 scalar_t__ tcp_skb_mss (struct sk_buff*) ; 
 int tcp_skb_pcount (struct sk_buff*) ; 

void tcp_newreno_mark_lost(struct sock *sk, bool snd_una_advanced)
{
	const u8 state = inet_csk(sk)->icsk_ca_state;
	struct tcp_sock *tp = tcp_sk(sk);

	if ((state < TCP_CA_Recovery && tp->sacked_out >= tp->reordering) ||
	    (state == TCP_CA_Recovery && snd_una_advanced)) {
		struct sk_buff *skb = tcp_rtx_queue_head(sk);
		u32 mss;

		if (TCP_SKB_CB(skb)->sacked & TCPCB_LOST)
			return;

		mss = tcp_skb_mss(skb);
		if (tcp_skb_pcount(skb) > 1 && skb->len > mss)
			tcp_fragment(sk, TCP_FRAG_IN_RTX_QUEUE, skb,
				     mss, mss, GFP_ATOMIC);

		tcp_skb_mark_lost_uncond_verify(tp, skb);
	}
}