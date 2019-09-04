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
struct sock {size_t sk_protocol; } ;
struct netlink_sock {unsigned int subscriptions; } ;
struct TYPE_2__ {int /*<<< orphan*/  mc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sk_del_bind_node (struct sock*) ; 
 TYPE_1__* nl_table ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  sk_add_bind_node (struct sock*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
netlink_update_subscriptions(struct sock *sk, unsigned int subscriptions)
{
	struct netlink_sock *nlk = nlk_sk(sk);

	if (nlk->subscriptions && !subscriptions)
		__sk_del_bind_node(sk);
	else if (!nlk->subscriptions && subscriptions)
		sk_add_bind_node(sk, &nl_table[sk->sk_protocol].mc_list);
	nlk->subscriptions = subscriptions;
}