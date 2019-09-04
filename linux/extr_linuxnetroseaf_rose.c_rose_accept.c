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
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_type; scalar_t__ sk_state; int /*<<< orphan*/  sk_ack_backlog; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ERESTARTSYS ; 
 int EWOULDBLOCK ; 
 int O_NONBLOCK ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_graft (struct sock*,struct socket*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int rose_accept(struct socket *sock, struct socket *newsock, int flags,
		       bool kern)
{
	struct sk_buff *skb;
	struct sock *newsk;
	DEFINE_WAIT(wait);
	struct sock *sk;
	int err = 0;

	if ((sk = sock->sk) == NULL)
		return -EINVAL;

	lock_sock(sk);
	if (sk->sk_type != SOCK_SEQPACKET) {
		err = -EOPNOTSUPP;
		goto out_release;
	}

	if (sk->sk_state != TCP_LISTEN) {
		err = -EINVAL;
		goto out_release;
	}

	/*
	 *	The write queue this time is holding sockets ready to use
	 *	hooked into the SABM we saved
	 */
	for (;;) {
		prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);

		skb = skb_dequeue(&sk->sk_receive_queue);
		if (skb)
			break;

		if (flags & O_NONBLOCK) {
			err = -EWOULDBLOCK;
			break;
		}
		if (!signal_pending(current)) {
			release_sock(sk);
			schedule();
			lock_sock(sk);
			continue;
		}
		err = -ERESTARTSYS;
		break;
	}
	finish_wait(sk_sleep(sk), &wait);
	if (err)
		goto out_release;

	newsk = skb->sk;
	sock_graft(newsk, newsock);

	/* Now attach up the new socket */
	skb->sk = NULL;
	kfree_skb(skb);
	sk->sk_ack_backlog--;

out_release:
	release_sock(sk);

	return err;
}