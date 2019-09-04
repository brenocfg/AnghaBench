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
struct nl_info {struct net* nl_net; } ;
struct TYPE_2__ {struct fib6_info* fib6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct fib6_table {int /*<<< orphan*/  tb6_lock; } ;
struct fib6_info {struct fib6_table* fib6_table; } ;

/* Variables and functions */
 int ENOENT ; 
 int fib6_del (struct fib6_info*,struct nl_info*) ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ip6_del_rt(struct fib6_info *rt, struct nl_info *info)
{
	struct net *net = info->nl_net;
	struct fib6_table *table;
	int err;

	if (rt == net->ipv6.fib6_null_entry) {
		err = -ENOENT;
		goto out;
	}

	table = rt->fib6_table;
	spin_lock_bh(&table->tb6_lock);
	err = fib6_del(rt, info);
	spin_unlock_bh(&table->tb6_lock);

out:
	fib6_info_release(rt);
	return err;
}