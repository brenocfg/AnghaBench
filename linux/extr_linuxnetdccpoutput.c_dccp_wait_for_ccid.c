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
struct sock {scalar_t__ sk_err; int /*<<< orphan*/  sk_write_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 long schedule_timeout (unsigned long) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int dccp_wait_for_ccid(struct sock *sk, unsigned long delay)
{
	DEFINE_WAIT(wait);
	long remaining;

	prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);
	sk->sk_write_pending++;
	release_sock(sk);

	remaining = schedule_timeout(delay);

	lock_sock(sk);
	sk->sk_write_pending--;
	finish_wait(sk_sleep(sk), &wait);

	if (signal_pending(current) || sk->sk_err)
		return -1;
	return remaining;
}