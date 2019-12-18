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
struct net_device {TYPE_1__* l3mdev_ops; } ;
struct net {int dummy; } ;
struct flowi {int /*<<< orphan*/  flowi_iif; int /*<<< orphan*/  flowi_oif; } ;
struct fib_lookup_arg {int /*<<< orphan*/  table; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* l3mdev_fib_table ) (struct net_device*) ;} ;

/* Variables and functions */
 struct net_device* dev_get_by_index_rcu (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_is_l3_master (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 

int l3mdev_fib_rule_match(struct net *net, struct flowi *fl,
			  struct fib_lookup_arg *arg)
{
	struct net_device *dev;
	int rc = 0;

	rcu_read_lock();

	dev = dev_get_by_index_rcu(net, fl->flowi_oif);
	if (dev && netif_is_l3_master(dev) &&
	    dev->l3mdev_ops->l3mdev_fib_table) {
		arg->table = dev->l3mdev_ops->l3mdev_fib_table(dev);
		rc = 1;
		goto out;
	}

	dev = dev_get_by_index_rcu(net, fl->flowi_iif);
	if (dev && netif_is_l3_master(dev) &&
	    dev->l3mdev_ops->l3mdev_fib_table) {
		arg->table = dev->l3mdev_ops->l3mdev_fib_table(dev);
		rc = 1;
		goto out;
	}

out:
	rcu_read_unlock();

	return rc;
}