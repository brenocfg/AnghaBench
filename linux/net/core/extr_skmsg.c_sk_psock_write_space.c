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
struct sock {int dummy; } ;
struct sk_psock {void (* saved_write_space ) (struct sock*) ;int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_PSOCK_TX_ENABLED ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct sk_psock* sk_psock (struct sock*) ; 
 scalar_t__ sk_psock_test_state (struct sk_psock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sk_psock_write_space(struct sock *sk)
{
	struct sk_psock *psock;
	void (*write_space)(struct sock *sk);

	rcu_read_lock();
	psock = sk_psock(sk);
	if (likely(psock && sk_psock_test_state(psock, SK_PSOCK_TX_ENABLED)))
		schedule_work(&psock->work);
	write_space = psock->saved_write_space;
	rcu_read_unlock();
	write_space(sk);
}