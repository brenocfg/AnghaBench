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
struct tcp_sock {int packets_out; scalar_t__ snd_nxt; scalar_t__ tlp_high_seq; int /*<<< orphan*/  snd_cwnd; } ;
struct sock {int /*<<< orphan*/  sk_state; int /*<<< orphan*/  tcp_rtx_queue; } ;
struct sk_buff {int len; } ;
struct TYPE_2__ {scalar_t__ icsk_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LINUX_MIB_TCPLOSSPROBES ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_FRAG_IN_RTX_QUEUE ; 
 int /*<<< orphan*/  TCP_NAGLE_OFF ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ __tcp_retransmit_skb (struct sock*,struct sk_buff*,int) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 struct sk_buff* skb_rb_last (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_rb_next (struct sk_buff*) ; 
 scalar_t__ skb_still_in_host_queue (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int tcp_current_mss (struct sock*) ; 
 int tcp_fragment (struct sock*,int /*<<< orphan*/ ,struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_rearm_rto (struct sock*) ; 
 struct sk_buff* tcp_send_head (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int tcp_skb_pcount (struct sk_buff*) ; 
 scalar_t__ tcp_snd_wnd_test (struct tcp_sock*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  tcp_write_xmit (struct sock*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void tcp_send_loss_probe(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct sk_buff *skb;
	int pcount;
	int mss = tcp_current_mss(sk);

	skb = tcp_send_head(sk);
	if (skb && tcp_snd_wnd_test(tp, skb, mss)) {
		pcount = tp->packets_out;
		tcp_write_xmit(sk, mss, TCP_NAGLE_OFF, 2, GFP_ATOMIC);
		if (tp->packets_out > pcount)
			goto probe_sent;
		goto rearm_timer;
	}
	skb = skb_rb_last(&sk->tcp_rtx_queue);
	if (unlikely(!skb)) {
		WARN_ONCE(tp->packets_out,
			  "invalid inflight: %u state %u cwnd %u mss %d\n",
			  tp->packets_out, sk->sk_state, tp->snd_cwnd, mss);
		inet_csk(sk)->icsk_pending = 0;
		return;
	}

	/* At most one outstanding TLP retransmission. */
	if (tp->tlp_high_seq)
		goto rearm_timer;

	if (skb_still_in_host_queue(sk, skb))
		goto rearm_timer;

	pcount = tcp_skb_pcount(skb);
	if (WARN_ON(!pcount))
		goto rearm_timer;

	if ((pcount > 1) && (skb->len > (pcount - 1) * mss)) {
		if (unlikely(tcp_fragment(sk, TCP_FRAG_IN_RTX_QUEUE, skb,
					  (pcount - 1) * mss, mss,
					  GFP_ATOMIC)))
			goto rearm_timer;
		skb = skb_rb_next(skb);
	}

	if (WARN_ON(!skb || !tcp_skb_pcount(skb)))
		goto rearm_timer;

	if (__tcp_retransmit_skb(sk, skb, 1))
		goto rearm_timer;

	/* Record snd_nxt for loss detection. */
	tp->tlp_high_seq = tp->snd_nxt;

probe_sent:
	NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPLOSSPROBES);
	/* Reset s.t. tcp_rearm_rto will restart timer from now */
	inet_csk(sk)->icsk_pending = 0;
rearm_timer:
	tcp_rearm_rto(sk);
}