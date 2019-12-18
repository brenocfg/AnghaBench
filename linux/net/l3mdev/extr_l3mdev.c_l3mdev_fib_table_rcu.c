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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {TYPE_1__* l3mdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* l3mdev_fib_table ) (struct net_device const*) ;} ;

/* Variables and functions */
 struct net_device* netdev_master_upper_dev_get_rcu (struct net_device*) ; 
 scalar_t__ netif_is_l3_master (struct net_device const*) ; 
 scalar_t__ netif_is_l3_slave (struct net_device const*) ; 
 int /*<<< orphan*/  stub1 (struct net_device const*) ; 
 int /*<<< orphan*/  stub2 (struct net_device const*) ; 

u32 l3mdev_fib_table_rcu(const struct net_device *dev)
{
	u32 tb_id = 0;

	if (!dev)
		return 0;

	if (netif_is_l3_master(dev)) {
		if (dev->l3mdev_ops->l3mdev_fib_table)
			tb_id = dev->l3mdev_ops->l3mdev_fib_table(dev);
	} else if (netif_is_l3_slave(dev)) {
		/* Users of netdev_master_upper_dev_get_rcu need non-const,
		 * but current inet_*type functions take a const
		 */
		struct net_device *_dev = (struct net_device *) dev;
		const struct net_device *master;

		master = netdev_master_upper_dev_get_rcu(_dev);
		if (master &&
		    master->l3mdev_ops->l3mdev_fib_table)
			tb_id = master->l3mdev_ops->l3mdev_fib_table(master);
	}

	return tb_id;
}