#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcp_sock {int /*<<< orphan*/  packets_out; int /*<<< orphan*/  snd_wnd; scalar_t__ lsndtime; } ;
struct sock {scalar_t__ sk_err_soft; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LINUX_MIB_TCPABORTONMEMORY ; 
 int TCP_RTO_MAX ; 
 int TCP_TIMEWAIT_LEN ; 
 int /*<<< orphan*/  __NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ tcp_check_oom (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_done (struct sock*) ; 
 scalar_t__ tcp_jiffies32 ; 
 int /*<<< orphan*/  tcp_send_active_reset (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static int tcp_out_of_resources(struct sock *sk, bool do_reset)
{
	struct tcp_sock *tp = tcp_sk(sk);
	int shift = 0;

	/* If peer does not open window for long time, or did not transmit
	 * anything for long time, penalize it. */
	if ((s32)(tcp_jiffies32 - tp->lsndtime) > 2*TCP_RTO_MAX || !do_reset)
		shift++;

	/* If some dubious ICMP arrived, penalize even more. */
	if (sk->sk_err_soft)
		shift++;

	if (tcp_check_oom(sk, shift)) {
		/* Catch exceptional cases, when connection requires reset.
		 *      1. Last segment was sent recently. */
		if ((s32)(tcp_jiffies32 - tp->lsndtime) <= TCP_TIMEWAIT_LEN ||
		    /*  2. Window is closed. */
		    (!tp->snd_wnd && !tp->packets_out))
			do_reset = true;
		if (do_reset)
			tcp_send_active_reset(sk, GFP_ATOMIC);
		tcp_done(sk);
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONMEMORY);
		return 1;
	}

	if (!check_net(sock_net(sk))) {
		/* Not possible to send reset; just close */
		tcp_done(sk);
		return 1;
	}

	return 0;
}