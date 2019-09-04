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
struct sock {int sk_shutdown; scalar_t__ sk_err; int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RCV_SHUTDOWN ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_WAITDATA ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_clear_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_set_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static long bt_sock_data_wait(struct sock *sk, long timeo)
{
	DECLARE_WAITQUEUE(wait, current);

	add_wait_queue(sk_sleep(sk), &wait);
	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);

		if (!skb_queue_empty(&sk->sk_receive_queue))
			break;

		if (sk->sk_err || (sk->sk_shutdown & RCV_SHUTDOWN))
			break;

		if (signal_pending(current) || !timeo)
			break;

		sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
		release_sock(sk);
		timeo = schedule_timeout(timeo);
		lock_sock(sk);
		sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	}

	__set_current_state(TASK_RUNNING);
	remove_wait_queue(sk_sleep(sk), &wait);
	return timeo;
}