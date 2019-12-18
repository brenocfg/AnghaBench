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
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EBADFD ; 
 scalar_t__ LLCP_LISTEN ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  SS_CONNECTED ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue_exclusive (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  lock_sock_nested (struct sock*,int /*<<< orphan*/ ) ; 
 struct sock* nfc_llcp_accept_dequeue (struct sock*,struct socket*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int sock_intr_errno (long) ; 
 long sock_rcvtimeo (struct sock*,int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int llcp_sock_accept(struct socket *sock, struct socket *newsock,
			    int flags, bool kern)
{
	DECLARE_WAITQUEUE(wait, current);
	struct sock *sk = sock->sk, *new_sk;
	long timeo;
	int ret = 0;

	pr_debug("parent %p\n", sk);

	lock_sock_nested(sk, SINGLE_DEPTH_NESTING);

	if (sk->sk_state != LLCP_LISTEN) {
		ret = -EBADFD;
		goto error;
	}

	timeo = sock_rcvtimeo(sk, flags & O_NONBLOCK);

	/* Wait for an incoming connection. */
	add_wait_queue_exclusive(sk_sleep(sk), &wait);
	while (!(new_sk = nfc_llcp_accept_dequeue(sk, newsock))) {
		set_current_state(TASK_INTERRUPTIBLE);

		if (!timeo) {
			ret = -EAGAIN;
			break;
		}

		if (signal_pending(current)) {
			ret = sock_intr_errno(timeo);
			break;
		}

		release_sock(sk);
		timeo = schedule_timeout(timeo);
		lock_sock_nested(sk, SINGLE_DEPTH_NESTING);
	}
	__set_current_state(TASK_RUNNING);
	remove_wait_queue(sk_sleep(sk), &wait);

	if (ret)
		goto error;

	newsock->state = SS_CONNECTED;

	pr_debug("new socket %p\n", new_sk);

error:
	release_sock(sk);

	return ret;
}