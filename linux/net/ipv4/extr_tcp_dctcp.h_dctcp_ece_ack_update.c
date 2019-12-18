#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
typedef  enum tcp_ca_event { ____Placeholder_tcp_ca_event } tcp_ca_event ;
struct TYPE_4__ {int pending; } ;
struct TYPE_6__ {TYPE_1__ icsk_ack; } ;
struct TYPE_5__ {scalar_t__ rcv_nxt; } ;

/* Variables and functions */
 int CA_EVENT_ECN_IS_CE ; 
 int ICSK_ACK_NOW ; 
 int ICSK_ACK_TIMER ; 
 int /*<<< orphan*/  __tcp_send_ack (struct sock*,scalar_t__) ; 
 int /*<<< orphan*/  dctcp_ece_ack_cwr (struct sock*,scalar_t__) ; 
 TYPE_3__* inet_csk (struct sock*) ; 
 TYPE_2__* tcp_sk (struct sock*) ; 

__attribute__((used)) static inline void dctcp_ece_ack_update(struct sock *sk, enum tcp_ca_event evt,
					u32 *prior_rcv_nxt, u32 *ce_state)
{
	u32 new_ce_state = (evt == CA_EVENT_ECN_IS_CE) ? 1 : 0;

	if (*ce_state != new_ce_state) {
		/* CE state has changed, force an immediate ACK to
		 * reflect the new CE state. If an ACK was delayed,
		 * send that first to reflect the prior CE state.
		 */
		if (inet_csk(sk)->icsk_ack.pending & ICSK_ACK_TIMER) {
			dctcp_ece_ack_cwr(sk, *ce_state);
			__tcp_send_ack(sk, *prior_rcv_nxt);
		}
		inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_NOW;
	}
	*prior_rcv_nxt = tcp_sk(sk)->rcv_nxt;
	*ce_state = new_ce_state;
	dctcp_ece_ack_cwr(sk, new_ce_state);
}