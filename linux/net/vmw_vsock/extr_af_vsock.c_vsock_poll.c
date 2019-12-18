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
struct vsock_sock {int peer_shutdown; } ;
struct socket {scalar_t__ type; struct sock* sk; } ;
struct sock {int sk_shutdown; scalar_t__ sk_state; int /*<<< orphan*/  sk_receive_queue; scalar_t__ sk_err; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {int (* notify_poll_in ) (struct vsock_sock*,int,int*) ;int (* notify_poll_out ) (struct vsock_sock*,int,int*) ;scalar_t__ (* stream_is_active ) (struct vsock_sock*) ;} ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDHUP ; 
 int EPOLLRDNORM ; 
 int EPOLLWRBAND ; 
 int EPOLLWRNORM ; 
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 int SHUTDOWN_MASK ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ TCP_CLOSE ; 
 scalar_t__ TCP_CLOSING ; 
 scalar_t__ TCP_ESTABLISHED ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_empty_lockless (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct vsock_sock*) ; 
 int stub2 (struct vsock_sock*,int,int*) ; 
 int stub3 (struct vsock_sock*,int,int*) ; 
 TYPE_1__* transport ; 
 int /*<<< orphan*/  vsock_is_accept_queue_empty (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static __poll_t vsock_poll(struct file *file, struct socket *sock,
			       poll_table *wait)
{
	struct sock *sk;
	__poll_t mask;
	struct vsock_sock *vsk;

	sk = sock->sk;
	vsk = vsock_sk(sk);

	poll_wait(file, sk_sleep(sk), wait);
	mask = 0;

	if (sk->sk_err)
		/* Signify that there has been an error on this socket. */
		mask |= EPOLLERR;

	/* INET sockets treat local write shutdown and peer write shutdown as a
	 * case of EPOLLHUP set.
	 */
	if ((sk->sk_shutdown == SHUTDOWN_MASK) ||
	    ((sk->sk_shutdown & SEND_SHUTDOWN) &&
	     (vsk->peer_shutdown & SEND_SHUTDOWN))) {
		mask |= EPOLLHUP;
	}

	if (sk->sk_shutdown & RCV_SHUTDOWN ||
	    vsk->peer_shutdown & SEND_SHUTDOWN) {
		mask |= EPOLLRDHUP;
	}

	if (sock->type == SOCK_DGRAM) {
		/* For datagram sockets we can read if there is something in
		 * the queue and write as long as the socket isn't shutdown for
		 * sending.
		 */
		if (!skb_queue_empty_lockless(&sk->sk_receive_queue) ||
		    (sk->sk_shutdown & RCV_SHUTDOWN)) {
			mask |= EPOLLIN | EPOLLRDNORM;
		}

		if (!(sk->sk_shutdown & SEND_SHUTDOWN))
			mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;

	} else if (sock->type == SOCK_STREAM) {
		lock_sock(sk);

		/* Listening sockets that have connections in their accept
		 * queue can be read.
		 */
		if (sk->sk_state == TCP_LISTEN
		    && !vsock_is_accept_queue_empty(sk))
			mask |= EPOLLIN | EPOLLRDNORM;

		/* If there is something in the queue then we can read. */
		if (transport->stream_is_active(vsk) &&
		    !(sk->sk_shutdown & RCV_SHUTDOWN)) {
			bool data_ready_now = false;
			int ret = transport->notify_poll_in(
					vsk, 1, &data_ready_now);
			if (ret < 0) {
				mask |= EPOLLERR;
			} else {
				if (data_ready_now)
					mask |= EPOLLIN | EPOLLRDNORM;

			}
		}

		/* Sockets whose connections have been closed, reset, or
		 * terminated should also be considered read, and we check the
		 * shutdown flag for that.
		 */
		if (sk->sk_shutdown & RCV_SHUTDOWN ||
		    vsk->peer_shutdown & SEND_SHUTDOWN) {
			mask |= EPOLLIN | EPOLLRDNORM;
		}

		/* Connected sockets that can produce data can be written. */
		if (sk->sk_state == TCP_ESTABLISHED) {
			if (!(sk->sk_shutdown & SEND_SHUTDOWN)) {
				bool space_avail_now = false;
				int ret = transport->notify_poll_out(
						vsk, 1, &space_avail_now);
				if (ret < 0) {
					mask |= EPOLLERR;
				} else {
					if (space_avail_now)
						/* Remove EPOLLWRBAND since INET
						 * sockets are not setting it.
						 */
						mask |= EPOLLOUT | EPOLLWRNORM;

				}
			}
		}

		/* Simulate INET socket poll behaviors, which sets
		 * EPOLLOUT|EPOLLWRNORM when peer is closed and nothing to read,
		 * but local send is not shutdown.
		 */
		if (sk->sk_state == TCP_CLOSE || sk->sk_state == TCP_CLOSING) {
			if (!(sk->sk_shutdown & SEND_SHUTDOWN))
				mask |= EPOLLOUT | EPOLLWRNORM;

		}

		release_sock(sk);
	}

	return mask;
}