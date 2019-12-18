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
struct socket {struct sock* sk; } ;
struct sock {int sk_shutdown; int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_error_queue; scalar_t__ sk_err; } ;
struct sctp_sock {TYPE_1__* ep; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  asocs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSED ; 
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLPRI ; 
 int EPOLLRDHUP ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  LISTENING ; 
 int RCV_SHUTDOWN ; 
 int SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_SELECT_ERR_QUEUE ; 
 int /*<<< orphan*/  TCP ; 
 int /*<<< orphan*/  UDP ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sctp_sock* sctp_sk (struct sock*) ; 
 scalar_t__ sctp_sstate (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_style (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_writeable (struct sock*) ; 
 int /*<<< orphan*/  sk_set_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_empty_lockless (int /*<<< orphan*/ *) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_rps_record_flow (struct sock*) ; 

__poll_t sctp_poll(struct file *file, struct socket *sock, poll_table *wait)
{
	struct sock *sk = sock->sk;
	struct sctp_sock *sp = sctp_sk(sk);
	__poll_t mask;

	poll_wait(file, sk_sleep(sk), wait);

	sock_rps_record_flow(sk);

	/* A TCP-style listening socket becomes readable when the accept queue
	 * is not empty.
	 */
	if (sctp_style(sk, TCP) && sctp_sstate(sk, LISTENING))
		return (!list_empty(&sp->ep->asocs)) ?
			(EPOLLIN | EPOLLRDNORM) : 0;

	mask = 0;

	/* Is there any exceptional events?  */
	if (sk->sk_err || !skb_queue_empty_lockless(&sk->sk_error_queue))
		mask |= EPOLLERR |
			(sock_flag(sk, SOCK_SELECT_ERR_QUEUE) ? EPOLLPRI : 0);
	if (sk->sk_shutdown & RCV_SHUTDOWN)
		mask |= EPOLLRDHUP | EPOLLIN | EPOLLRDNORM;
	if (sk->sk_shutdown == SHUTDOWN_MASK)
		mask |= EPOLLHUP;

	/* Is it readable?  Reconsider this code with TCP-style support.  */
	if (!skb_queue_empty_lockless(&sk->sk_receive_queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* The association is either gone or not ready.  */
	if (!sctp_style(sk, UDP) && sctp_sstate(sk, CLOSED))
		return mask;

	/* Is it writable?  */
	if (sctp_writeable(sk)) {
		mask |= EPOLLOUT | EPOLLWRNORM;
	} else {
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);
		/*
		 * Since the socket is not locked, the buffer
		 * might be made available after the writeable check and
		 * before the bit is set.  This could cause a lost I/O
		 * signal.  tcp_poll() has a race breaker for this race
		 * condition.  Based on their implementation, we put
		 * in the following code to cover it as well.
		 */
		if (sctp_writeable(sk))
			mask |= EPOLLOUT | EPOLLWRNORM;
	}
	return mask;
}