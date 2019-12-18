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
struct vsock_sock {int rejected; } ;
struct socket {scalar_t__ type; int /*<<< orphan*/  state; struct sock* sk; } ;
struct sock {scalar_t__ sk_state; int sk_err; int /*<<< orphan*/  sk_ack_backlog; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  SS_CONNECTED ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  lock_sock_nested (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 long schedule_timeout (long) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  sock_graft (struct sock*,struct socket*) ; 
 int sock_intr_errno (long) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 struct sock* vsock_dequeue_accept (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int vsock_accept(struct socket *sock, struct socket *newsock, int flags,
			bool kern)
{
	struct sock *listener;
	int err;
	struct sock *connected;
	struct vsock_sock *vconnected;
	long timeout;
	DEFINE_WAIT(wait);

	err = 0;
	listener = sock->sk;

	lock_sock(listener);

	if (sock->type != SOCK_STREAM) {
		err = -EOPNOTSUPP;
		goto out;
	}

	if (listener->sk_state != TCP_LISTEN) {
		err = -EINVAL;
		goto out;
	}

	/* Wait for children sockets to appear; these are the new sockets
	 * created upon connection establishment.
	 */
	timeout = sock_sndtimeo(listener, flags & O_NONBLOCK);
	prepare_to_wait(sk_sleep(listener), &wait, TASK_INTERRUPTIBLE);

	while ((connected = vsock_dequeue_accept(listener)) == NULL &&
	       listener->sk_err == 0) {
		release_sock(listener);
		timeout = schedule_timeout(timeout);
		finish_wait(sk_sleep(listener), &wait);
		lock_sock(listener);

		if (signal_pending(current)) {
			err = sock_intr_errno(timeout);
			goto out;
		} else if (timeout == 0) {
			err = -EAGAIN;
			goto out;
		}

		prepare_to_wait(sk_sleep(listener), &wait, TASK_INTERRUPTIBLE);
	}
	finish_wait(sk_sleep(listener), &wait);

	if (listener->sk_err)
		err = -listener->sk_err;

	if (connected) {
		listener->sk_ack_backlog--;

		lock_sock_nested(connected, SINGLE_DEPTH_NESTING);
		vconnected = vsock_sk(connected);

		/* If the listener socket has received an error, then we should
		 * reject this socket and return.  Note that we simply mark the
		 * socket rejected, drop our reference, and let the cleanup
		 * function handle the cleanup; the fact that we found it in
		 * the listener's accept queue guarantees that the cleanup
		 * function hasn't run yet.
		 */
		if (err) {
			vconnected->rejected = true;
		} else {
			newsock->state = SS_CONNECTED;
			sock_graft(connected, newsock);
		}

		release_sock(connected);
		sock_put(connected);
	}

out:
	release_sock(listener);
	return err;
}