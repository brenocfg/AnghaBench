#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int rcv_wscale; } ;
struct tcp_sock {scalar_t__ rcv_wnd; scalar_t__ pred_flags; TYPE_2__ rx_opt; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  rcv_wup; } ;
struct sock {int dummy; } ;
struct TYPE_5__ {scalar_t__ sysctl_tcp_workaround_signed_windows; } ;
struct TYPE_7__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  LINUX_MIB_TCPFROMZEROWINDOWADV ; 
 int /*<<< orphan*/  LINUX_MIB_TCPTOZEROWINDOWADV ; 
 int /*<<< orphan*/  LINUX_MIB_TCPWANTZEROWINDOWADV ; 
 unsigned int MAX_TCP_WINDOW ; 
 int /*<<< orphan*/  NET_INC_STATS (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ __tcp_select_window (struct sock*) ; 
 scalar_t__ min (scalar_t__,unsigned int) ; 
 TYPE_3__* sock_net (struct sock*) ; 
 scalar_t__ tcp_receive_window (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static u16 tcp_select_window(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	u32 old_win = tp->rcv_wnd;
	u32 cur_win = tcp_receive_window(tp);
	u32 new_win = __tcp_select_window(sk);

	/* Never shrink the offered window */
	if (new_win < cur_win) {
		/* Danger Will Robinson!
		 * Don't update rcv_wup/rcv_wnd here or else
		 * we will not be able to advertise a zero
		 * window in time.  --DaveM
		 *
		 * Relax Will Robinson.
		 */
		if (new_win == 0)
			NET_INC_STATS(sock_net(sk),
				      LINUX_MIB_TCPWANTZEROWINDOWADV);
		new_win = ALIGN(cur_win, 1 << tp->rx_opt.rcv_wscale);
	}
	tp->rcv_wnd = new_win;
	tp->rcv_wup = tp->rcv_nxt;

	/* Make sure we do not exceed the maximum possible
	 * scaled window.
	 */
	if (!tp->rx_opt.rcv_wscale &&
	    sock_net(sk)->ipv4.sysctl_tcp_workaround_signed_windows)
		new_win = min(new_win, MAX_TCP_WINDOW);
	else
		new_win = min(new_win, (65535U << tp->rx_opt.rcv_wscale));

	/* RFC1323 scaling applied */
	new_win >>= tp->rx_opt.rcv_wscale;

	/* If we advertise zero window, disable fast path. */
	if (new_win == 0) {
		tp->pred_flags = 0;
		if (old_win)
			NET_INC_STATS(sock_net(sk),
				      LINUX_MIB_TCPTOZEROWINDOWADV);
	} else if (old_win == 0) {
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPFROMZEROWINDOWADV);
	}

	return new_win;
}