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
struct net_device {scalar_t__ rtnl_link_ops; } ;

/* Variables and functions */
 struct net_device* netdev_master_upper_dev_get_rcu (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static bool rtnl_have_link_slave_info(const struct net_device *dev)
{
	struct net_device *master_dev;
	bool ret = false;

	rcu_read_lock();

	master_dev = netdev_master_upper_dev_get_rcu((struct net_device *)dev);
	if (master_dev && master_dev->rtnl_link_ops)
		ret = true;
	rcu_read_unlock();
	return ret;
}