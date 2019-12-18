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
struct sock {int dummy; } ;
struct netlink_table {int /*<<< orphan*/  hash; } ;
struct netlink_compare_arg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  netlink_compare_arg_init (struct netlink_compare_arg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_rhashtable_params ; 
 TYPE_1__* nlk_sk (struct sock*) ; 
 int rhashtable_lookup_insert_key (int /*<<< orphan*/ *,struct netlink_compare_arg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int __netlink_insert(struct netlink_table *table, struct sock *sk)
{
	struct netlink_compare_arg arg;

	netlink_compare_arg_init(&arg, sock_net(sk), nlk_sk(sk)->portid);
	return rhashtable_lookup_insert_key(&table->hash, &arg,
					    &nlk_sk(sk)->node,
					    netlink_rhashtable_params);
}