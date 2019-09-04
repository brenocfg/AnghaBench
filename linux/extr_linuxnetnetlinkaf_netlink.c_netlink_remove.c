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
struct sock {size_t sk_protocol; int /*<<< orphan*/  sk_refcnt; } ;
struct netlink_table {int /*<<< orphan*/  hash; } ;
struct TYPE_2__ {scalar_t__ subscriptions; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 size_t NETLINK_GENERIC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __sk_del_bind_node (struct sock*) ; 
 int /*<<< orphan*/  __sock_put (struct sock*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genl_sk_destructing_cnt ; 
 int /*<<< orphan*/  netlink_rhashtable_params ; 
 int /*<<< orphan*/  netlink_table_grab () ; 
 int /*<<< orphan*/  netlink_table_ungrab () ; 
 int /*<<< orphan*/  netlink_update_listeners (struct sock*) ; 
 struct netlink_table* nl_table ; 
 TYPE_1__* nlk_sk (struct sock*) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netlink_remove(struct sock *sk)
{
	struct netlink_table *table;

	table = &nl_table[sk->sk_protocol];
	if (!rhashtable_remove_fast(&table->hash, &nlk_sk(sk)->node,
				    netlink_rhashtable_params)) {
		WARN_ON(refcount_read(&sk->sk_refcnt) == 1);
		__sock_put(sk);
	}

	netlink_table_grab();
	if (nlk_sk(sk)->subscriptions) {
		__sk_del_bind_node(sk);
		netlink_update_listeners(sk);
	}
	if (sk->sk_protocol == NETLINK_GENERIC)
		atomic_inc(&genl_sk_destructing_cnt);
	netlink_table_ungrab();
}