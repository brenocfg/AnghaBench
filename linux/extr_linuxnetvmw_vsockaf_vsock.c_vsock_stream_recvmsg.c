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
struct vsock_transport_recv_notify_data {int dummy; } ;
struct vsock_sock {int peer_shutdown; } ;
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; int sk_shutdown; scalar_t__ sk_err; } ;
struct msghdr {int dummy; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ s64 ;
struct TYPE_2__ {size_t (* stream_rcvhiwat ) (struct vsock_sock*) ;int (* notify_recv_init ) (struct vsock_sock*,size_t,struct vsock_transport_recv_notify_data*) ;int (* notify_recv_pre_block ) (struct vsock_sock*,size_t,struct vsock_transport_recv_notify_data*) ;int (* notify_recv_pre_dequeue ) (struct vsock_sock*,size_t,struct vsock_transport_recv_notify_data*) ;size_t (* stream_dequeue ) (struct vsock_sock*,struct msghdr*,size_t,int) ;int (* notify_recv_post_dequeue ) (struct vsock_sock*,size_t,size_t,int,struct vsock_transport_recv_notify_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int MSG_DONTWAIT ; 
 int MSG_OOB ; 
 int MSG_PEEK ; 
 int MSG_WAITALL ; 
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 long schedule_timeout (long) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int sock_intr_errno (long) ; 
 size_t sock_rcvlowat (struct sock*,int,size_t) ; 
 long sock_rcvtimeo (struct sock*,int) ; 
 size_t stub1 (struct vsock_sock*) ; 
 int stub2 (struct vsock_sock*,size_t,struct vsock_transport_recv_notify_data*) ; 
 int stub3 (struct vsock_sock*,size_t,struct vsock_transport_recv_notify_data*) ; 
 int stub4 (struct vsock_sock*,size_t,struct vsock_transport_recv_notify_data*) ; 
 size_t stub5 (struct vsock_sock*,struct msghdr*,size_t,int) ; 
 int stub6 (struct vsock_sock*,size_t,size_t,int,struct vsock_transport_recv_notify_data*) ; 
 TYPE_1__* transport ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 
 scalar_t__ vsock_stream_has_data (struct vsock_sock*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int
vsock_stream_recvmsg(struct socket *sock, struct msghdr *msg, size_t len,
		     int flags)
{
	struct sock *sk;
	struct vsock_sock *vsk;
	int err;
	size_t target;
	ssize_t copied;
	long timeout;
	struct vsock_transport_recv_notify_data recv_data;

	DEFINE_WAIT(wait);

	sk = sock->sk;
	vsk = vsock_sk(sk);
	err = 0;

	lock_sock(sk);

	if (sk->sk_state != TCP_ESTABLISHED) {
		/* Recvmsg is supposed to return 0 if a peer performs an
		 * orderly shutdown. Differentiate between that case and when a
		 * peer has not connected or a local shutdown occured with the
		 * SOCK_DONE flag.
		 */
		if (sock_flag(sk, SOCK_DONE))
			err = 0;
		else
			err = -ENOTCONN;

		goto out;
	}

	if (flags & MSG_OOB) {
		err = -EOPNOTSUPP;
		goto out;
	}

	/* We don't check peer_shutdown flag here since peer may actually shut
	 * down, but there can be data in the queue that a local socket can
	 * receive.
	 */
	if (sk->sk_shutdown & RCV_SHUTDOWN) {
		err = 0;
		goto out;
	}

	/* It is valid on Linux to pass in a zero-length receive buffer.  This
	 * is not an error.  We may as well bail out now.
	 */
	if (!len) {
		err = 0;
		goto out;
	}

	/* We must not copy less than target bytes into the user's buffer
	 * before returning successfully, so we wait for the consume queue to
	 * have that much data to consume before dequeueing.  Note that this
	 * makes it impossible to handle cases where target is greater than the
	 * queue size.
	 */
	target = sock_rcvlowat(sk, flags & MSG_WAITALL, len);
	if (target >= transport->stream_rcvhiwat(vsk)) {
		err = -ENOMEM;
		goto out;
	}
	timeout = sock_rcvtimeo(sk, flags & MSG_DONTWAIT);
	copied = 0;

	err = transport->notify_recv_init(vsk, target, &recv_data);
	if (err < 0)
		goto out;


	while (1) {
		s64 ready;

		prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);
		ready = vsock_stream_has_data(vsk);

		if (ready == 0) {
			if (sk->sk_err != 0 ||
			    (sk->sk_shutdown & RCV_SHUTDOWN) ||
			    (vsk->peer_shutdown & SEND_SHUTDOWN)) {
				finish_wait(sk_sleep(sk), &wait);
				break;
			}
			/* Don't wait for non-blocking sockets. */
			if (timeout == 0) {
				err = -EAGAIN;
				finish_wait(sk_sleep(sk), &wait);
				break;
			}

			err = transport->notify_recv_pre_block(
					vsk, target, &recv_data);
			if (err < 0) {
				finish_wait(sk_sleep(sk), &wait);
				break;
			}
			release_sock(sk);
			timeout = schedule_timeout(timeout);
			lock_sock(sk);

			if (signal_pending(current)) {
				err = sock_intr_errno(timeout);
				finish_wait(sk_sleep(sk), &wait);
				break;
			} else if (timeout == 0) {
				err = -EAGAIN;
				finish_wait(sk_sleep(sk), &wait);
				break;
			}
		} else {
			ssize_t read;

			finish_wait(sk_sleep(sk), &wait);

			if (ready < 0) {
				/* Invalid queue pair content. XXX This should
				* be changed to a connection reset in a later
				* change.
				*/

				err = -ENOMEM;
				goto out;
			}

			err = transport->notify_recv_pre_dequeue(
					vsk, target, &recv_data);
			if (err < 0)
				break;

			read = transport->stream_dequeue(
					vsk, msg,
					len - copied, flags);
			if (read < 0) {
				err = -ENOMEM;
				break;
			}

			copied += read;

			err = transport->notify_recv_post_dequeue(
					vsk, target, read,
					!(flags & MSG_PEEK), &recv_data);
			if (err < 0)
				goto out;

			if (read >= target || flags & MSG_PEEK)
				break;

			target -= read;
		}
	}

	if (sk->sk_err)
		err = -sk->sk_err;
	else if (sk->sk_shutdown & RCV_SHUTDOWN)
		err = 0;

	if (copied > 0)
		err = copied;

out:
	release_sock(sk);
	return err;
}