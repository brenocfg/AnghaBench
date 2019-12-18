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
struct nl_info {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct fib6_table {int /*<<< orphan*/  tb6_lock; int /*<<< orphan*/  tb6_root; } ;
struct fib6_info {struct fib6_table* fib6_table; } ;

/* Variables and functions */
 int fib6_add (int /*<<< orphan*/ *,struct fib6_info*,struct nl_info*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ip6_ins_rt(struct fib6_info *rt, struct nl_info *info,
			struct netlink_ext_ack *extack)
{
	int err;
	struct fib6_table *table;

	table = rt->fib6_table;
	spin_lock_bh(&table->tb6_lock);
	err = fib6_add(&table->tb6_root, rt, info, extack);
	spin_unlock_bh(&table->tb6_lock);

	return err;
}