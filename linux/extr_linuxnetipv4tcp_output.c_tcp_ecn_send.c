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
struct tcphdr {int cwr; int ece; } ;
struct tcp_sock {int ecn_flags; int /*<<< orphan*/  snd_nxt; } ;
struct sock {int dummy; } ;
struct sk_buff {int len; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq; } ;
struct TYPE_3__ {int /*<<< orphan*/  gso_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  INET_ECN_dontxmit (struct sock*) ; 
 int /*<<< orphan*/  INET_ECN_xmit (struct sock*) ; 
 int /*<<< orphan*/  SKB_GSO_TCP_ECN ; 
 int TCP_ECN_DEMAND_CWR ; 
 int TCP_ECN_OK ; 
 int TCP_ECN_QUEUE_CWR ; 
 TYPE_2__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_ca_needs_ecn (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void tcp_ecn_send(struct sock *sk, struct sk_buff *skb,
			 struct tcphdr *th, int tcp_header_len)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (tp->ecn_flags & TCP_ECN_OK) {
		/* Not-retransmitted data segment: set ECT and inject CWR. */
		if (skb->len != tcp_header_len &&
		    !before(TCP_SKB_CB(skb)->seq, tp->snd_nxt)) {
			INET_ECN_xmit(sk);
			if (tp->ecn_flags & TCP_ECN_QUEUE_CWR) {
				tp->ecn_flags &= ~TCP_ECN_QUEUE_CWR;
				th->cwr = 1;
				skb_shinfo(skb)->gso_type |= SKB_GSO_TCP_ECN;
			}
		} else if (!tcp_ca_needs_ecn(sk)) {
			/* ACK or retransmitted segment: clear ECT|CE */
			INET_ECN_dontxmit(sk);
		}
		if (tp->ecn_flags & TCP_ECN_DEMAND_CWR)
			th->ece = 1;
	}
}