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
struct rtnl_link_stats64 {unsigned long rx_dropped; unsigned long tx_dropped; unsigned long rx_nohandler; } ;
struct net_device_ops {int /*<<< orphan*/ * (* ndo_get_stats ) (struct net_device*) ;int /*<<< orphan*/  (* ndo_get_stats64 ) (struct net_device*,struct rtnl_link_stats64*) ;} ;
struct net_device {int /*<<< orphan*/  rx_nohandler; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  stats; struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rtnl_link_stats64*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_stats_to_stats64 (struct rtnl_link_stats64*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct rtnl_link_stats64*) ; 
 int /*<<< orphan*/ * stub2 (struct net_device*) ; 

struct rtnl_link_stats64 *dev_get_stats(struct net_device *dev,
					struct rtnl_link_stats64 *storage)
{
	const struct net_device_ops *ops = dev->netdev_ops;

	if (ops->ndo_get_stats64) {
		memset(storage, 0, sizeof(*storage));
		ops->ndo_get_stats64(dev, storage);
	} else if (ops->ndo_get_stats) {
		netdev_stats_to_stats64(storage, ops->ndo_get_stats(dev));
	} else {
		netdev_stats_to_stats64(storage, &dev->stats);
	}
	storage->rx_dropped += (unsigned long)atomic_long_read(&dev->rx_dropped);
	storage->tx_dropped += (unsigned long)atomic_long_read(&dev->tx_dropped);
	storage->rx_nohandler += (unsigned long)atomic_long_read(&dev->rx_nohandler);
	return storage;
}