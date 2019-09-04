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
struct usbnet {int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings*) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ax88179_get_link_ksettings(struct net_device *net,
				      struct ethtool_link_ksettings *cmd)
{
	struct usbnet *dev = netdev_priv(net);

	mii_ethtool_get_link_ksettings(&dev->mii, cmd);

	return 0;
}