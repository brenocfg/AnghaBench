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
struct sock {int /*<<< orphan*/  sk_filter; } ;
struct sk_filter {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_FILTER_LOCKED ; 
 int /*<<< orphan*/  lockdep_sock_is_held (struct sock*) ; 
 struct sk_filter* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_filter_uncharge (struct sock*,struct sk_filter*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

int sk_detach_filter(struct sock *sk)
{
	int ret = -ENOENT;
	struct sk_filter *filter;

	if (sock_flag(sk, SOCK_FILTER_LOCKED))
		return -EPERM;

	filter = rcu_dereference_protected(sk->sk_filter,
					   lockdep_sock_is_held(sk));
	if (filter) {
		RCU_INIT_POINTER(sk->sk_filter, NULL);
		sk_filter_uncharge(sk, filter);
		ret = 0;
	}

	return ret;
}