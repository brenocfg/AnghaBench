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
struct net_failover_info {int /*<<< orphan*/  primary_dev; int /*<<< orphan*/  standby_dev; int /*<<< orphan*/  failover_stats; } ;
struct TYPE_2__ {scalar_t__ parent; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_get_stats (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_mc_unsync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dev_uc_unsync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  net_failover_compute_features (struct net_device*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*,int /*<<< orphan*/ ) ; 
 struct net_failover_info* netdev_priv (struct net_device*) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_vids_del_by_dev (struct net_device*,struct net_device*) ; 

__attribute__((used)) static int net_failover_slave_unregister(struct net_device *slave_dev,
					 struct net_device *failover_dev)
{
	struct net_device *standby_dev, *primary_dev;
	struct net_failover_info *nfo_info;
	bool slave_is_standby;

	nfo_info = netdev_priv(failover_dev);
	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	standby_dev = rtnl_dereference(nfo_info->standby_dev);

	if (WARN_ON_ONCE(slave_dev != primary_dev && slave_dev != standby_dev))
		return -ENODEV;

	vlan_vids_del_by_dev(slave_dev, failover_dev);
	dev_uc_unsync(slave_dev, failover_dev);
	dev_mc_unsync(slave_dev, failover_dev);
	dev_close(slave_dev);

	nfo_info = netdev_priv(failover_dev);
	dev_get_stats(failover_dev, &nfo_info->failover_stats);

	slave_is_standby = slave_dev->dev.parent == failover_dev->dev.parent;
	if (slave_is_standby) {
		RCU_INIT_POINTER(nfo_info->standby_dev, NULL);
	} else {
		RCU_INIT_POINTER(nfo_info->primary_dev, NULL);
		if (standby_dev) {
			failover_dev->min_mtu = standby_dev->min_mtu;
			failover_dev->max_mtu = standby_dev->max_mtu;
		}
	}

	dev_put(slave_dev);

	net_failover_compute_features(failover_dev);

	netdev_info(failover_dev, "failover %s slave:%s unregistered\n",
		    slave_is_standby ? "standby" : "primary", slave_dev->name);

	return 0;
}