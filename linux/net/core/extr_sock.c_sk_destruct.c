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
struct sock {int /*<<< orphan*/  sk_rcu; int /*<<< orphan*/  sk_reuseport_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_RCU_FREE ; 
 int /*<<< orphan*/  __sk_destruct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reuseport_detach_sock (struct sock*) ; 
 int sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

void sk_destruct(struct sock *sk)
{
	bool use_call_rcu = sock_flag(sk, SOCK_RCU_FREE);

	if (rcu_access_pointer(sk->sk_reuseport_cb)) {
		reuseport_detach_sock(sk);
		use_call_rcu = true;
	}

	if (use_call_rcu)
		call_rcu(&sk->sk_rcu, __sk_destruct);
	else
		__sk_destruct(&sk->sk_rcu);
}