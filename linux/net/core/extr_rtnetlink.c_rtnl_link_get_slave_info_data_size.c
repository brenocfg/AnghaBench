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
struct rtnl_link_ops {size_t (* get_slave_size ) (struct net_device*,struct net_device const*) ;} ;
struct nlattr {int dummy; } ;
struct net_device {struct rtnl_link_ops* rtnl_link_ops; } ;

/* Variables and functions */
 struct net_device* netdev_master_upper_dev_get_rcu (struct net_device*) ; 
 size_t nla_total_size (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 size_t stub1 (struct net_device*,struct net_device const*) ; 

__attribute__((used)) static size_t rtnl_link_get_slave_info_data_size(const struct net_device *dev)
{
	struct net_device *master_dev;
	const struct rtnl_link_ops *ops;
	size_t size = 0;

	rcu_read_lock();

	master_dev = netdev_master_upper_dev_get_rcu((struct net_device *)dev);
	if (!master_dev)
		goto out;

	ops = master_dev->rtnl_link_ops;
	if (!ops || !ops->get_slave_size)
		goto out;
	/* IFLA_INFO_SLAVE_DATA + nested data */
	size = nla_total_size(sizeof(struct nlattr)) +
	       ops->get_slave_size(master_dev, dev);

out:
	rcu_read_unlock();
	return size;
}