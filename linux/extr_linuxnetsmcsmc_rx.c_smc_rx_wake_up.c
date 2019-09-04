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
struct socket_wq {int /*<<< orphan*/  wait; } ;
struct sock {scalar_t__ sk_shutdown; scalar_t__ sk_state; int /*<<< orphan*/  sk_wq; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLPRI ; 
 int EPOLLRDBAND ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  POLL_HUP ; 
 int /*<<< orphan*/  POLL_IN ; 
 scalar_t__ SHUTDOWN_MASK ; 
 scalar_t__ SMC_CLOSED ; 
 int /*<<< orphan*/  SOCK_WAKE_WAITD ; 
 struct socket_wq* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_wake_async (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skwq_has_sleeper (struct socket_wq*) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync_poll (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void smc_rx_wake_up(struct sock *sk)
{
	struct socket_wq *wq;

	/* derived from sock_def_readable() */
	/* called already in smc_listen_work() */
	rcu_read_lock();
	wq = rcu_dereference(sk->sk_wq);
	if (skwq_has_sleeper(wq))
		wake_up_interruptible_sync_poll(&wq->wait, EPOLLIN | EPOLLPRI |
						EPOLLRDNORM | EPOLLRDBAND);
	sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_IN);
	if ((sk->sk_shutdown == SHUTDOWN_MASK) ||
	    (sk->sk_state == SMC_CLOSED))
		sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_HUP);
	rcu_read_unlock();
}