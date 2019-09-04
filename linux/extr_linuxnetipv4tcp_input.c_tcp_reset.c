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
struct sock {int sk_state; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;int /*<<< orphan*/  sk_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNREFUSED ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
#define  TCP_CLOSE 130 
#define  TCP_CLOSE_WAIT 129 
#define  TCP_SYN_SENT 128 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_done (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_queue_purge (struct sock*) ; 
 int /*<<< orphan*/  trace_tcp_receive_reset (struct sock*) ; 

void tcp_reset(struct sock *sk)
{
	trace_tcp_receive_reset(sk);

	/* We want the right error as BSD sees it (and indeed as we do). */
	switch (sk->sk_state) {
	case TCP_SYN_SENT:
		sk->sk_err = ECONNREFUSED;
		break;
	case TCP_CLOSE_WAIT:
		sk->sk_err = EPIPE;
		break;
	case TCP_CLOSE:
		return;
	default:
		sk->sk_err = ECONNRESET;
	}
	/* This barrier is coupled with smp_rmb() in tcp_poll() */
	smp_wmb();

	tcp_write_queue_purge(sk);
	tcp_done(sk);

	if (!sock_flag(sk, SOCK_DEAD))
		sk->sk_error_report(sk);
}