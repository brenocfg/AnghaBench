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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct sock {TYPE_1__* sk_socket; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EPOLLOUT ; 
 int EPOLLWRBAND ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/ * sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  sock_writeable (struct sock*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void tap_sock_write_space(struct sock *sk)
{
	wait_queue_head_t *wqueue;

	if (!sock_writeable(sk) ||
	    !test_and_clear_bit(SOCKWQ_ASYNC_NOSPACE, &sk->sk_socket->flags))
		return;

	wqueue = sk_sleep(sk);
	if (wqueue && waitqueue_active(wqueue))
		wake_up_interruptible_poll(wqueue, EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND);
}