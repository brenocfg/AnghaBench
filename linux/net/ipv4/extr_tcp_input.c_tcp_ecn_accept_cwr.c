#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pending; } ;
struct TYPE_8__ {TYPE_1__ icsk_ack; } ;
struct TYPE_7__ {scalar_t__ cwr; } ;
struct TYPE_6__ {int /*<<< orphan*/  ecn_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICSK_ACK_NOW ; 
 int /*<<< orphan*/  TCP_ECN_DEMAND_CWR ; 
 TYPE_4__* inet_csk (struct sock*) ; 
 TYPE_3__* tcp_hdr (struct sk_buff const*) ; 
 TYPE_2__* tcp_sk (struct sock*) ; 

__attribute__((used)) static void tcp_ecn_accept_cwr(struct sock *sk, const struct sk_buff *skb)
{
	if (tcp_hdr(skb)->cwr) {
		tcp_sk(sk)->ecn_flags &= ~TCP_ECN_DEMAND_CWR;

		/* If the sender is telling us it has entered CWR, then its
		 * cwnd may be very low (even just 1 packet), so we should ACK
		 * immediately.
		 */
		inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_NOW;
	}
}