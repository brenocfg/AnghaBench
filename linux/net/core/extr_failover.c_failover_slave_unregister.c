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
struct net_device {int priv_flags; int /*<<< orphan*/  perm_addr; } ;
struct failover_ops {int /*<<< orphan*/  (* slave_unregister ) (struct net_device*,struct net_device*) ;scalar_t__ (* slave_pre_unregister ) (struct net_device*,struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int IFF_FAILOVER_SLAVE ; 
 int IFF_LIVE_RENAME_OK ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 struct net_device* failover_get_bymac (int /*<<< orphan*/ ,struct failover_ops**) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (struct net_device*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  netif_is_failover_slave (struct net_device*) ; 
 scalar_t__ stub1 (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,struct net_device*) ; 

int failover_slave_unregister(struct net_device *slave_dev)
{
	struct net_device *failover_dev;
	struct failover_ops *fops;

	if (!netif_is_failover_slave(slave_dev))
		goto done;

	ASSERT_RTNL();

	failover_dev = failover_get_bymac(slave_dev->perm_addr, &fops);
	if (!failover_dev)
		goto done;

	if (fops && fops->slave_pre_unregister &&
	    fops->slave_pre_unregister(slave_dev, failover_dev))
		goto done;

	netdev_rx_handler_unregister(slave_dev);
	netdev_upper_dev_unlink(slave_dev, failover_dev);
	slave_dev->priv_flags &= ~(IFF_FAILOVER_SLAVE | IFF_LIVE_RENAME_OK);

	if (fops && fops->slave_unregister &&
	    !fops->slave_unregister(slave_dev, failover_dev))
		return NOTIFY_OK;

done:
	return NOTIFY_DONE;
}