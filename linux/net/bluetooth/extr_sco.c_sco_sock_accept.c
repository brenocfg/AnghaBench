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
struct socket {int /*<<< orphan*/  state; struct sock* sk; } ;
struct sock {scalar_t__ sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,...) ; 
 scalar_t__ BT_LISTEN ; 
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EBADFD ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SS_CONNECTED ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue_exclusive (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sock* bt_accept_dequeue (struct sock*,struct socket*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int sock_intr_errno (long) ; 
 long sock_rcvtimeo (struct sock*,int) ; 
 int /*<<< orphan*/  wait ; 
 long wait_woken (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static int sco_sock_accept(struct socket *sock, struct socket *newsock,
			   int flags, bool kern)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	struct sock *sk = sock->sk, *ch;
	long timeo;
	int err = 0;

	lock_sock(sk);

	timeo = sock_rcvtimeo(sk, flags & O_NONBLOCK);

	BT_DBG("sk %p timeo %ld", sk, timeo);

	/* Wait for an incoming connection. (wake-one). */
	add_wait_queue_exclusive(sk_sleep(sk), &wait);
	while (1) {
		if (sk->sk_state != BT_LISTEN) {
			err = -EBADFD;
			break;
		}

		ch = bt_accept_dequeue(sk, newsock);
		if (ch)
			break;

		if (!timeo) {
			err = -EAGAIN;
			break;
		}

		if (signal_pending(current)) {
			err = sock_intr_errno(timeo);
			break;
		}

		release_sock(sk);

		timeo = wait_woken(&wait, TASK_INTERRUPTIBLE, timeo);
		lock_sock(sk);
	}
	remove_wait_queue(sk_sleep(sk), &wait);

	if (err)
		goto done;

	newsock->state = SS_CONNECTED;

	BT_DBG("new socket %p", ch);

done:
	release_sock(sk);
	return err;
}