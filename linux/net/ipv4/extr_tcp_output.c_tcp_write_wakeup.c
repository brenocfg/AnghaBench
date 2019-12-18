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
struct tcp_sock {unsigned int pushed_seq; scalar_t__ snd_una; int /*<<< orphan*/  snd_up; } ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {unsigned int len; } ;
struct TYPE_2__ {unsigned int seq; unsigned int end_seq; int /*<<< orphan*/  tcp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TCPHDR_PSH ; 
 scalar_t__ TCP_CLOSE ; 
 int /*<<< orphan*/  TCP_FRAG_IN_WRITE_QUEUE ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ before (unsigned int,unsigned int) ; 
 scalar_t__ between (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int tcp_current_mss (struct sock*) ; 
 int /*<<< orphan*/  tcp_event_new_data_sent (struct sock*,struct sk_buff*) ; 
 scalar_t__ tcp_fragment (struct sock*,int /*<<< orphan*/ ,struct sk_buff*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 struct sk_buff* tcp_send_head (struct sock*) ; 
 int /*<<< orphan*/  tcp_set_skb_tso_segs (struct sk_buff*,unsigned int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_skb_pcount (struct sk_buff*) ; 
 int tcp_transmit_skb (struct sock*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 unsigned int tcp_wnd_end (struct tcp_sock*) ; 
 int tcp_xmit_probe_skb (struct sock*,int,int) ; 

int tcp_write_wakeup(struct sock *sk, int mib)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct sk_buff *skb;

	if (sk->sk_state == TCP_CLOSE)
		return -1;

	skb = tcp_send_head(sk);
	if (skb && before(TCP_SKB_CB(skb)->seq, tcp_wnd_end(tp))) {
		int err;
		unsigned int mss = tcp_current_mss(sk);
		unsigned int seg_size = tcp_wnd_end(tp) - TCP_SKB_CB(skb)->seq;

		if (before(tp->pushed_seq, TCP_SKB_CB(skb)->end_seq))
			tp->pushed_seq = TCP_SKB_CB(skb)->end_seq;

		/* We are probing the opening of a window
		 * but the window size is != 0
		 * must have been a result SWS avoidance ( sender )
		 */
		if (seg_size < TCP_SKB_CB(skb)->end_seq - TCP_SKB_CB(skb)->seq ||
		    skb->len > mss) {
			seg_size = min(seg_size, mss);
			TCP_SKB_CB(skb)->tcp_flags |= TCPHDR_PSH;
			if (tcp_fragment(sk, TCP_FRAG_IN_WRITE_QUEUE,
					 skb, seg_size, mss, GFP_ATOMIC))
				return -1;
		} else if (!tcp_skb_pcount(skb))
			tcp_set_skb_tso_segs(skb, mss);

		TCP_SKB_CB(skb)->tcp_flags |= TCPHDR_PSH;
		err = tcp_transmit_skb(sk, skb, 1, GFP_ATOMIC);
		if (!err)
			tcp_event_new_data_sent(sk, skb);
		return err;
	} else {
		if (between(tp->snd_up, tp->snd_una + 1, tp->snd_una + 0xFFFF))
			tcp_xmit_probe_skb(sk, 1, mib);
		return tcp_xmit_probe_skb(sk, 0, mib);
	}
}