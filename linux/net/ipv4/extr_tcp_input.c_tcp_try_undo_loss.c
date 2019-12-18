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
struct tcp_sock {scalar_t__ is_sack_reneg; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ icsk_retransmits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGUNDO (struct sock*,char*) ; 
 int /*<<< orphan*/  LINUX_MIB_TCPLOSSUNDO ; 
 int /*<<< orphan*/  LINUX_MIB_TCPSPURIOUSRTOS ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_CA_Open ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ tcp_is_sack (struct tcp_sock*) ; 
 scalar_t__ tcp_may_undo (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_set_ca_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_undo_cwnd_reduction (struct sock*,int) ; 

__attribute__((used)) static bool tcp_try_undo_loss(struct sock *sk, bool frto_undo)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (frto_undo || tcp_may_undo(tp)) {
		tcp_undo_cwnd_reduction(sk, true);

		DBGUNDO(sk, "partial loss");
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPLOSSUNDO);
		if (frto_undo)
			NET_INC_STATS(sock_net(sk),
					LINUX_MIB_TCPSPURIOUSRTOS);
		inet_csk(sk)->icsk_retransmits = 0;
		if (frto_undo || tcp_is_sack(tp)) {
			tcp_set_ca_state(sk, TCP_CA_Open);
			tp->is_sack_reneg = 0;
		}
		return true;
	}
	return false;
}