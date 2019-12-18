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
struct tcp_sock {int urg_data; int /*<<< orphan*/  copied_seq; int /*<<< orphan*/  urg_seq; int /*<<< orphan*/  fastopen_rsk; } ;
struct socket {struct sock* sk; } ;
struct sock {int sk_shutdown; int /*<<< orphan*/  sk_error_queue; scalar_t__ sk_err; TYPE_1__* sk_socket; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_4__ {scalar_t__ defer_connect; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLPRI ; 
 int EPOLLRDHUP ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  INT_MAX ; 
 int RCV_SHUTDOWN ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int SEND_SHUTDOWN ; 
 int SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int /*<<< orphan*/  SOCK_URGINLINE ; 
 int TCP_CLOSE ; 
 int TCP_LISTEN ; 
 int TCP_SYN_RECV ; 
 int TCP_SYN_SENT ; 
 int TCP_URG_VALID ; 
 int inet_csk_listen_poll (struct sock*) ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int inet_sk_state_load (struct sock*) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_set_bit (int /*<<< orphan*/ ,struct sock*) ; 
 scalar_t__ sk_stream_is_writeable (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_empty_lockless (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_poll_wait (struct file*,struct socket*,int /*<<< orphan*/ *) ; 
 int sock_rcvlowat (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_stream_is_readable (struct tcp_sock const*,int,struct sock*) ; 

__poll_t tcp_poll(struct file *file, struct socket *sock, poll_table *wait)
{
	__poll_t mask;
	struct sock *sk = sock->sk;
	const struct tcp_sock *tp = tcp_sk(sk);
	int state;

	sock_poll_wait(file, sock, wait);

	state = inet_sk_state_load(sk);
	if (state == TCP_LISTEN)
		return inet_csk_listen_poll(sk);

	/* Socket is not locked. We are protected from async events
	 * by poll logic and correct handling of state changes
	 * made by other threads is impossible in any case.
	 */

	mask = 0;

	/*
	 * EPOLLHUP is certainly not done right. But poll() doesn't
	 * have a notion of HUP in just one direction, and for a
	 * socket the read side is more interesting.
	 *
	 * Some poll() documentation says that EPOLLHUP is incompatible
	 * with the EPOLLOUT/POLLWR flags, so somebody should check this
	 * all. But careful, it tends to be safer to return too many
	 * bits than too few, and you can easily break real applications
	 * if you don't tell them that something has hung up!
	 *
	 * Check-me.
	 *
	 * Check number 1. EPOLLHUP is _UNMASKABLE_ event (see UNIX98 and
	 * our fs/select.c). It means that after we received EOF,
	 * poll always returns immediately, making impossible poll() on write()
	 * in state CLOSE_WAIT. One solution is evident --- to set EPOLLHUP
	 * if and only if shutdown has been made in both directions.
	 * Actually, it is interesting to look how Solaris and DUX
	 * solve this dilemma. I would prefer, if EPOLLHUP were maskable,
	 * then we could set it on SND_SHUTDOWN. BTW examples given
	 * in Stevens' books assume exactly this behaviour, it explains
	 * why EPOLLHUP is incompatible with EPOLLOUT.	--ANK
	 *
	 * NOTE. Check for TCP_CLOSE is added. The goal is to prevent
	 * blocking on fresh not-connected or disconnected socket. --ANK
	 */
	if (sk->sk_shutdown == SHUTDOWN_MASK || state == TCP_CLOSE)
		mask |= EPOLLHUP;
	if (sk->sk_shutdown & RCV_SHUTDOWN)
		mask |= EPOLLIN | EPOLLRDNORM | EPOLLRDHUP;

	/* Connected or passive Fast Open socket? */
	if (state != TCP_SYN_SENT &&
	    (state != TCP_SYN_RECV || rcu_access_pointer(tp->fastopen_rsk))) {
		int target = sock_rcvlowat(sk, 0, INT_MAX);

		if (READ_ONCE(tp->urg_seq) == READ_ONCE(tp->copied_seq) &&
		    !sock_flag(sk, SOCK_URGINLINE) &&
		    tp->urg_data)
			target++;

		if (tcp_stream_is_readable(tp, target, sk))
			mask |= EPOLLIN | EPOLLRDNORM;

		if (!(sk->sk_shutdown & SEND_SHUTDOWN)) {
			if (sk_stream_is_writeable(sk)) {
				mask |= EPOLLOUT | EPOLLWRNORM;
			} else {  /* send SIGIO later */
				sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);
				set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);

				/* Race breaker. If space is freed after
				 * wspace test but before the flags are set,
				 * IO signal will be lost. Memory barrier
				 * pairs with the input side.
				 */
				smp_mb__after_atomic();
				if (sk_stream_is_writeable(sk))
					mask |= EPOLLOUT | EPOLLWRNORM;
			}
		} else
			mask |= EPOLLOUT | EPOLLWRNORM;

		if (tp->urg_data & TCP_URG_VALID)
			mask |= EPOLLPRI;
	} else if (state == TCP_SYN_SENT && inet_sk(sk)->defer_connect) {
		/* Active TCP fastopen socket with defer_connect
		 * Return EPOLLOUT so application can call write()
		 * in order for kernel to generate SYN+data
		 */
		mask |= EPOLLOUT | EPOLLWRNORM;
	}
	/* This barrier is coupled with smp_wmb() in tcp_reset() */
	smp_rmb();
	if (sk->sk_err || !skb_queue_empty_lockless(&sk->sk_error_queue))
		mask |= EPOLLERR;

	return mask;
}