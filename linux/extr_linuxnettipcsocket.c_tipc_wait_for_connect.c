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
struct sock {scalar_t__ sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 scalar_t__ TIPC_CONNECTING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int sk_wait_event (struct sock*,long*,int,int /*<<< orphan*/ *) ; 
 int sock_error (struct sock*) ; 
 int sock_intr_errno (long) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static int tipc_wait_for_connect(struct socket *sock, long *timeo_p)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	struct sock *sk = sock->sk;
	int done;

	do {
		int err = sock_error(sk);
		if (err)
			return err;
		if (!*timeo_p)
			return -ETIMEDOUT;
		if (signal_pending(current))
			return sock_intr_errno(*timeo_p);

		add_wait_queue(sk_sleep(sk), &wait);
		done = sk_wait_event(sk, timeo_p,
				     sk->sk_state != TIPC_CONNECTING, &wait);
		remove_wait_queue(sk_sleep(sk), &wait);
	} while (!done);
	return 0;
}