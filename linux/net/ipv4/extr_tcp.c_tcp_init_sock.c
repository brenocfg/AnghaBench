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
struct TYPE_4__ {int reo_wnd_steps; } ;
struct tcp_sock {unsigned int app_limited; TYPE_1__ rack; scalar_t__ tsoffset; int /*<<< orphan*/  reordering; int /*<<< orphan*/  mss_cache; int /*<<< orphan*/  snd_cwnd_clamp; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  snd_cwnd; int /*<<< orphan*/  rtt_min; int /*<<< orphan*/  mdev_us; int /*<<< orphan*/  tsorted_sent_queue; int /*<<< orphan*/  tsq_node; void* out_of_order_queue; } ;
struct sock {int /*<<< orphan*/  sk_route_forced_caps; int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_sndbuf; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_state; void* tcp_rtx_queue; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_sync_mss; int /*<<< orphan*/  icsk_rto; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sysctl_tcp_rmem; int /*<<< orphan*/ * sysctl_tcp_wmem; int /*<<< orphan*/  sysctl_tcp_reordering; } ;
struct TYPE_6__ {TYPE_2__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NETIF_F_GSO ; 
 void* RB_ROOT ; 
 int /*<<< orphan*/  SOCK_USE_WRITE_QUEUE ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  TCP_INFINITE_SSTHRESH ; 
 int /*<<< orphan*/  TCP_INIT_CWND ; 
 int /*<<< orphan*/  TCP_MSS_DEFAULT ; 
 int /*<<< orphan*/  TCP_TIMEOUT_INIT ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  jiffies_to_usecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minmax_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sk_sockets_allocated_inc (struct sock*) ; 
 int /*<<< orphan*/  sk_stream_write_space ; 
 TYPE_3__* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_assign_congestion_control (struct sock*) ; 
 int /*<<< orphan*/  tcp_init_xmit_timers (struct sock*) ; 
 int /*<<< orphan*/  tcp_jiffies32 ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_sync_mss ; 

void tcp_init_sock(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);

	tp->out_of_order_queue = RB_ROOT;
	sk->tcp_rtx_queue = RB_ROOT;
	tcp_init_xmit_timers(sk);
	INIT_LIST_HEAD(&tp->tsq_node);
	INIT_LIST_HEAD(&tp->tsorted_sent_queue);

	icsk->icsk_rto = TCP_TIMEOUT_INIT;
	tp->mdev_us = jiffies_to_usecs(TCP_TIMEOUT_INIT);
	minmax_reset(&tp->rtt_min, tcp_jiffies32, ~0U);

	/* So many TCP implementations out there (incorrectly) count the
	 * initial SYN frame in their delayed-ACK and congestion control
	 * algorithms that we must have the following bandaid to talk
	 * efficiently to them.  -DaveM
	 */
	tp->snd_cwnd = TCP_INIT_CWND;

	/* There's a bubble in the pipe until at least the first ACK. */
	tp->app_limited = ~0U;

	/* See draft-stevens-tcpca-spec-01 for discussion of the
	 * initialization of these values.
	 */
	tp->snd_ssthresh = TCP_INFINITE_SSTHRESH;
	tp->snd_cwnd_clamp = ~0;
	tp->mss_cache = TCP_MSS_DEFAULT;

	tp->reordering = sock_net(sk)->ipv4.sysctl_tcp_reordering;
	tcp_assign_congestion_control(sk);

	tp->tsoffset = 0;
	tp->rack.reo_wnd_steps = 1;

	sk->sk_state = TCP_CLOSE;

	sk->sk_write_space = sk_stream_write_space;
	sock_set_flag(sk, SOCK_USE_WRITE_QUEUE);

	icsk->icsk_sync_mss = tcp_sync_mss;

	WRITE_ONCE(sk->sk_sndbuf, sock_net(sk)->ipv4.sysctl_tcp_wmem[1]);
	WRITE_ONCE(sk->sk_rcvbuf, sock_net(sk)->ipv4.sysctl_tcp_rmem[1]);

	sk_sockets_allocated_inc(sk);
	sk->sk_route_forced_caps = NETIF_F_GSO;
}