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
struct TYPE_2__ {int /*<<< orphan*/  mdio_read; } ;
struct usbnet {TYPE_1__ mii; } ;
struct net_device {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (TYPE_1__*,struct ethtool_link_ksettings*) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

int usbnet_get_link_ksettings(struct net_device *net,
			      struct ethtool_link_ksettings *cmd)
{
	struct usbnet *dev = netdev_priv(net);

	if (!dev->mii.mdio_read)
		return -EOPNOTSUPP;

	mii_ethtool_get_link_ksettings(&dev->mii, cmd);

	return 0;
}