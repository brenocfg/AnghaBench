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
struct sock {int sk_state; } ;
struct inet_connection_sock {int icsk_pending; int /*<<< orphan*/  icsk_timeout; int /*<<< orphan*/  icsk_retransmit_timer; } ;

/* Variables and functions */
#define  ICSK_TIME_LOSS_PROBE 131 
#define  ICSK_TIME_PROBE0 130 
#define  ICSK_TIME_REO_TIMEOUT 129 
#define  ICSK_TIME_RETRANS 128 
 int TCPF_CLOSE ; 
 int TCPF_LISTEN ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  sk_mem_reclaim (struct sock*) ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_mstamp_refresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_probe_timer (struct sock*) ; 
 int /*<<< orphan*/  tcp_rack_reo_timeout (struct sock*) ; 
 int /*<<< orphan*/  tcp_retransmit_timer (struct sock*) ; 
 int /*<<< orphan*/  tcp_send_loss_probe (struct sock*) ; 
 int /*<<< orphan*/  tcp_sk (struct sock*) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tcp_write_timer_handler(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	int event;

	if (((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN)) ||
	    !icsk->icsk_pending)
		goto out;

	if (time_after(icsk->icsk_timeout, jiffies)) {
		sk_reset_timer(sk, &icsk->icsk_retransmit_timer, icsk->icsk_timeout);
		goto out;
	}

	tcp_mstamp_refresh(tcp_sk(sk));
	event = icsk->icsk_pending;

	switch (event) {
	case ICSK_TIME_REO_TIMEOUT:
		tcp_rack_reo_timeout(sk);
		break;
	case ICSK_TIME_LOSS_PROBE:
		tcp_send_loss_probe(sk);
		break;
	case ICSK_TIME_RETRANS:
		icsk->icsk_pending = 0;
		tcp_retransmit_timer(sk);
		break;
	case ICSK_TIME_PROBE0:
		icsk->icsk_pending = 0;
		tcp_probe_timer(sk);
		break;
	}

out:
	sk_mem_reclaim(sk);
}