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
struct TYPE_2__ {scalar_t__ reo_wnd_persist; } ;
struct tcp_sock {TYPE_1__ rack; int /*<<< orphan*/  undo_retrans; scalar_t__ undo_marker; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGUNDO (struct sock*,char*) ; 
 int /*<<< orphan*/  LINUX_MIB_TCPDSACKUNDO ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_RACK_RECOVERY_THRESH ; 
 scalar_t__ min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_undo_cwnd_reduction (struct sock*,int) ; 

__attribute__((used)) static bool tcp_try_undo_dsack(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (tp->undo_marker && !tp->undo_retrans) {
		tp->rack.reo_wnd_persist = min(TCP_RACK_RECOVERY_THRESH,
					       tp->rack.reo_wnd_persist + 1);
		DBGUNDO(sk, "D-SACK");
		tcp_undo_cwnd_reduction(sk, false);
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPDSACKUNDO);
		return true;
	}
	return false;
}