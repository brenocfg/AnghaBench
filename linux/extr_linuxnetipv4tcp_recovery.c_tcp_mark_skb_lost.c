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
struct tcp_sock {int /*<<< orphan*/  retrans_out; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int sacked; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPLOSTRETRANSMIT ; 
 int /*<<< orphan*/  NET_ADD_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int TCPCB_SACKED_RETRANS ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_skb_mark_lost_uncond_verify (struct tcp_sock*,struct sk_buff*) ; 
 scalar_t__ tcp_skb_pcount (struct sk_buff*) ; 

void tcp_mark_skb_lost(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);

	tcp_skb_mark_lost_uncond_verify(tp, skb);
	if (TCP_SKB_CB(skb)->sacked & TCPCB_SACKED_RETRANS) {
		/* Account for retransmits that are lost again */
		TCP_SKB_CB(skb)->sacked &= ~TCPCB_SACKED_RETRANS;
		tp->retrans_out -= tcp_skb_pcount(skb);
		NET_ADD_STATS(sock_net(sk), LINUX_MIB_TCPLOSTRETRANSMIT,
			      tcp_skb_pcount(skb));
	}
}