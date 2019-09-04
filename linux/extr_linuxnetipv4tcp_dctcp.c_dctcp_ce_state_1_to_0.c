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
struct tcp_sock {int /*<<< orphan*/  ecn_flags; int /*<<< orphan*/  rcv_nxt; } ;
struct sock {int dummy; } ;
struct dctcp {scalar_t__ ce_state; int /*<<< orphan*/  prior_rcv_nxt; } ;
struct TYPE_3__ {int pending; } ;
struct TYPE_4__ {TYPE_1__ icsk_ack; } ;

/* Variables and functions */
 int ICSK_ACK_NOW ; 
 int ICSK_ACK_TIMER ; 
 int /*<<< orphan*/  TCP_ECN_DEMAND_CWR ; 
 int /*<<< orphan*/  __tcp_send_ack (struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 struct dctcp* inet_csk_ca (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void dctcp_ce_state_1_to_0(struct sock *sk)
{
	struct dctcp *ca = inet_csk_ca(sk);
	struct tcp_sock *tp = tcp_sk(sk);

	if (ca->ce_state) {
		/* State has changed from CE=1 to CE=0, force an immediate
		 * ACK to reflect the new CE state. If an ACK was delayed,
		 * send that first to reflect the prior CE state.
		 */
		if (inet_csk(sk)->icsk_ack.pending & ICSK_ACK_TIMER)
			__tcp_send_ack(sk, ca->prior_rcv_nxt);
		inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_NOW;
	}

	ca->prior_rcv_nxt = tp->rcv_nxt;
	ca->ce_state = 0;

	tp->ecn_flags &= ~TCP_ECN_DEMAND_CWR;
}