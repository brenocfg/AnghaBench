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
struct TYPE_2__ {int ip_dsfield; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_EVENT_ECN_IS_CE ; 
 int /*<<< orphan*/  CA_EVENT_ECN_NO_CE ; 
#define  INET_ECN_CE 129 
 int INET_ECN_MASK ; 
#define  INET_ECN_NOT_ECT 128 
 int TCP_ECN_DEMAND_CWR ; 
 int TCP_ECN_SEEN ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff const*) ; 
 int /*<<< orphan*/  tcp_ca_event (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_ca_needs_ecn (struct sock*) ; 
 int /*<<< orphan*/  tcp_enter_quickack_mode (struct sock*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void __tcp_ecn_check_ce(struct sock *sk, const struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);

	switch (TCP_SKB_CB(skb)->ip_dsfield & INET_ECN_MASK) {
	case INET_ECN_NOT_ECT:
		/* Funny extension: if ECT is not set on a segment,
		 * and we already seen ECT on a previous segment,
		 * it is probably a retransmit.
		 */
		if (tp->ecn_flags & TCP_ECN_SEEN)
			tcp_enter_quickack_mode(sk, 2);
		break;
	case INET_ECN_CE:
		if (tcp_ca_needs_ecn(sk))
			tcp_ca_event(sk, CA_EVENT_ECN_IS_CE);

		if (!(tp->ecn_flags & TCP_ECN_DEMAND_CWR)) {
			/* Better not delay acks, sender can have a very low cwnd */
			tcp_enter_quickack_mode(sk, 2);
			tp->ecn_flags |= TCP_ECN_DEMAND_CWR;
		}
		tp->ecn_flags |= TCP_ECN_SEEN;
		break;
	default:
		if (tcp_ca_needs_ecn(sk))
			tcp_ca_event(sk, CA_EVENT_ECN_NO_CE);
		tp->ecn_flags |= TCP_ECN_SEEN;
		break;
	}
}