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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINVAL ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 long schedule_timeout (long) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int sock_intr_errno (long) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static struct sk_buff *dn_wait_for_connect(struct sock *sk, long *timeo)
{
	DEFINE_WAIT(wait);
	struct sk_buff *skb = NULL;
	int err = 0;

	prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);
	for(;;) {
		release_sock(sk);
		skb = skb_dequeue(&sk->sk_receive_queue);
		if (skb == NULL) {
			*timeo = schedule_timeout(*timeo);
			skb = skb_dequeue(&sk->sk_receive_queue);
		}
		lock_sock(sk);
		if (skb != NULL)
			break;
		err = -EINVAL;
		if (sk->sk_state != TCP_LISTEN)
			break;
		err = sock_intr_errno(*timeo);
		if (signal_pending(current))
			break;
		err = -EAGAIN;
		if (!*timeo)
			break;
		prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);
	}
	finish_wait(sk_sleep(sk), &wait);

	return skb == NULL ? ERR_PTR(err) : skb;
}