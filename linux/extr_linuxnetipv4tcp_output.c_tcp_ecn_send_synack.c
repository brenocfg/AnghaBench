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
struct tcp_sock {int ecn_flags; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INET_ECN_xmit (struct sock*) ; 
 int /*<<< orphan*/  TCPHDR_CWR ; 
 int /*<<< orphan*/  TCPHDR_ECE ; 
 int TCP_ECN_OK ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ tcp_bpf_ca_needs_ecn (struct sock*) ; 
 scalar_t__ tcp_ca_needs_ecn (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void tcp_ecn_send_synack(struct sock *sk, struct sk_buff *skb)
{
	const struct tcp_sock *tp = tcp_sk(sk);

	TCP_SKB_CB(skb)->tcp_flags &= ~TCPHDR_CWR;
	if (!(tp->ecn_flags & TCP_ECN_OK))
		TCP_SKB_CB(skb)->tcp_flags &= ~TCPHDR_ECE;
	else if (tcp_ca_needs_ecn(sk) ||
		 tcp_bpf_ca_needs_ecn(sk))
		INET_ECN_xmit(sk);
}