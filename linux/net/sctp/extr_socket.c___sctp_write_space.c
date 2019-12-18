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
struct socket_wq {int /*<<< orphan*/  wait; } ;
struct sock {int sk_shutdown; int /*<<< orphan*/  sk_wq; } ;
struct TYPE_2__ {struct sock* sk; } ;
struct sctp_association {int /*<<< orphan*/  wait; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_OUT ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_WAKE_SPACE ; 
 struct socket_wq* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ sctp_writeable (struct sock*) ; 
 scalar_t__ sctp_wspace (struct sctp_association*) ; 
 int /*<<< orphan*/  sock_wake_async (struct socket_wq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __sctp_write_space(struct sctp_association *asoc)
{
	struct sock *sk = asoc->base.sk;

	if (sctp_wspace(asoc) <= 0)
		return;

	if (waitqueue_active(&asoc->wait))
		wake_up_interruptible(&asoc->wait);

	if (sctp_writeable(sk)) {
		struct socket_wq *wq;

		rcu_read_lock();
		wq = rcu_dereference(sk->sk_wq);
		if (wq) {
			if (waitqueue_active(&wq->wait))
				wake_up_interruptible(&wq->wait);

			/* Note that we try to include the Async I/O support
			 * here by modeling from the current TCP/UDP code.
			 * We have not tested with it yet.
			 */
			if (!(sk->sk_shutdown & SEND_SHUTDOWN))
				sock_wake_async(wq, SOCK_WAKE_SPACE, POLL_OUT);
		}
		rcu_read_unlock();
	}
}