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
struct sock {int sk_shutdown; int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ENOTCONN ; 
 int RCV_SHUTDOWN ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_annotate_sleep () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int sock_error (struct sock*) ; 
 int sock_intr_errno (long) ; 
 int /*<<< orphan*/  wait ; 
 long wait_woken (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static int tipc_wait_for_rcvmsg(struct socket *sock, long *timeop)
{
	struct sock *sk = sock->sk;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	long timeo = *timeop;
	int err = sock_error(sk);

	if (err)
		return err;

	for (;;) {
		if (timeo && skb_queue_empty(&sk->sk_receive_queue)) {
			if (sk->sk_shutdown & RCV_SHUTDOWN) {
				err = -ENOTCONN;
				break;
			}
			add_wait_queue(sk_sleep(sk), &wait);
			release_sock(sk);
			timeo = wait_woken(&wait, TASK_INTERRUPTIBLE, timeo);
			sched_annotate_sleep();
			lock_sock(sk);
			remove_wait_queue(sk_sleep(sk), &wait);
		}
		err = 0;
		if (!skb_queue_empty(&sk->sk_receive_queue))
			break;
		err = -EAGAIN;
		if (!timeo)
			break;
		err = sock_intr_errno(timeo);
		if (signal_pending(current))
			break;

		err = sock_error(sk);
		if (err)
			break;
	}
	*timeop = timeo;
	return err;
}