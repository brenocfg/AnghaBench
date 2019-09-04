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
struct net_failover_info {int /*<<< orphan*/  primary_dev; int /*<<< orphan*/  standby_dev; } ;
struct TYPE_2__ {scalar_t__ parent; } ;
struct net_device {int features; int /*<<< orphan*/  name; TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  dev_is_pci (scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ,...) ; 
 struct net_failover_info* netdev_priv (struct net_device*) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ vlan_uses_dev (struct net_device*) ; 

__attribute__((used)) static int net_failover_slave_pre_register(struct net_device *slave_dev,
					   struct net_device *failover_dev)
{
	struct net_device *standby_dev, *primary_dev;
	struct net_failover_info *nfo_info;
	bool slave_is_standby;

	nfo_info = netdev_priv(failover_dev);
	standby_dev = rtnl_dereference(nfo_info->standby_dev);
	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	slave_is_standby = slave_dev->dev.parent == failover_dev->dev.parent;
	if (slave_is_standby ? standby_dev : primary_dev) {
		netdev_err(failover_dev, "%s attempting to register as slave dev when %s already present\n",
			   slave_dev->name,
			   slave_is_standby ? "standby" : "primary");
		return -EINVAL;
	}

	/* We want to allow only a direct attached VF device as a primary
	 * netdev. As there is no easy way to check for a VF device, restrict
	 * this to a pci device.
	 */
	if (!slave_is_standby && (!slave_dev->dev.parent ||
				  !dev_is_pci(slave_dev->dev.parent)))
		return -EINVAL;

	if (failover_dev->features & NETIF_F_VLAN_CHALLENGED &&
	    vlan_uses_dev(failover_dev)) {
		netdev_err(failover_dev, "Device %s is VLAN challenged and failover device has VLAN set up\n",
			   failover_dev->name);
		return -EINVAL;
	}

	return 0;
}