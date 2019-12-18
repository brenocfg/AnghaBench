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
struct tcp_sock {scalar_t__ packets_out; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ sysctl_tcp_retries2; } ;
struct net {TYPE_1__ ipv4; } ;
struct inet_connection_sock {scalar_t__ icsk_backoff; scalar_t__ icsk_probes_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICSK_TIME_PROBE0 ; 
 int /*<<< orphan*/  LINUX_MIB_TCPWINPROBE ; 
 unsigned long TCP_RESOURCE_PROBE_INTERVAL ; 
 int /*<<< orphan*/  TCP_RTO_MAX ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct net* sock_net (struct sock*) ; 
 unsigned long tcp_probe0_when (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_write_queue_empty (struct sock*) ; 
 int tcp_write_wakeup (struct sock*,int /*<<< orphan*/ ) ; 

void tcp_send_probe0(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	struct net *net = sock_net(sk);
	unsigned long timeout;
	int err;

	err = tcp_write_wakeup(sk, LINUX_MIB_TCPWINPROBE);

	if (tp->packets_out || tcp_write_queue_empty(sk)) {
		/* Cancel probe timer, if it is not required. */
		icsk->icsk_probes_out = 0;
		icsk->icsk_backoff = 0;
		return;
	}

	icsk->icsk_probes_out++;
	if (err <= 0) {
		if (icsk->icsk_backoff < net->ipv4.sysctl_tcp_retries2)
			icsk->icsk_backoff++;
		timeout = tcp_probe0_when(sk, TCP_RTO_MAX);
	} else {
		/* If packet was not sent due to local congestion,
		 * Let senders fight for local resources conservatively.
		 */
		timeout = TCP_RESOURCE_PROBE_INTERVAL;
	}
	tcp_reset_xmit_timer(sk, ICSK_TIME_PROBE0, timeout, TCP_RTO_MAX, NULL);
}