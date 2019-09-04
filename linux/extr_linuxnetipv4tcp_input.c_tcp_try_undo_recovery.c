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
struct TYPE_3__ {scalar_t__ reo_wnd_persist; } ;
struct tcp_sock {scalar_t__ snd_una; scalar_t__ high_seq; scalar_t__ is_sack_reneg; scalar_t__ retrans_stamp; TYPE_1__ rack; } ;
struct sock {int dummy; } ;
struct TYPE_4__ {scalar_t__ icsk_ca_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGUNDO (struct sock*,char*) ; 
 int LINUX_MIB_TCPFULLUNDO ; 
 int LINUX_MIB_TCPLOSSUNDO ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TCP_CA_Loss ; 
 int /*<<< orphan*/  TCP_CA_Open ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_any_retrans_done (struct sock*) ; 
 scalar_t__ tcp_is_reno (struct tcp_sock*) ; 
 scalar_t__ tcp_may_undo (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_set_ca_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_undo_cwnd_reduction (struct sock*,int) ; 

__attribute__((used)) static bool tcp_try_undo_recovery(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (tcp_may_undo(tp)) {
		int mib_idx;

		/* Happy end! We did not retransmit anything
		 * or our original transmission succeeded.
		 */
		DBGUNDO(sk, inet_csk(sk)->icsk_ca_state == TCP_CA_Loss ? "loss" : "retrans");
		tcp_undo_cwnd_reduction(sk, false);
		if (inet_csk(sk)->icsk_ca_state == TCP_CA_Loss)
			mib_idx = LINUX_MIB_TCPLOSSUNDO;
		else
			mib_idx = LINUX_MIB_TCPFULLUNDO;

		NET_INC_STATS(sock_net(sk), mib_idx);
	} else if (tp->rack.reo_wnd_persist) {
		tp->rack.reo_wnd_persist--;
	}
	if (tp->snd_una == tp->high_seq && tcp_is_reno(tp)) {
		/* Hold old state until something *above* high_seq
		 * is ACKed. For Reno it is MUST to prevent false
		 * fast retransmits (RFC2582). SACK TCP is safe. */
		if (!tcp_any_retrans_done(sk))
			tp->retrans_stamp = 0;
		return true;
	}
	tcp_set_ca_state(sk, TCP_CA_Open);
	tp->is_sack_reneg = 0;
	return false;
}