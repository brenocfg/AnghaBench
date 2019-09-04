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
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct lan78xx_net {int /*<<< orphan*/  intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int BMCR_LOOPBACK ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct lan78xx_net* netdev_priv (struct net_device*) ; 
 int phy_ethtool_ksettings_set (struct phy_device*,struct ethtool_link_ksettings const*) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan78xx_set_link_ksettings(struct net_device *net,
				      const struct ethtool_link_ksettings *cmd)
{
	struct lan78xx_net *dev = netdev_priv(net);
	struct phy_device *phydev = net->phydev;
	int ret = 0;
	int temp;

	ret = usb_autopm_get_interface(dev->intf);
	if (ret < 0)
		return ret;

	/* change speed & duplex */
	ret = phy_ethtool_ksettings_set(phydev, cmd);

	if (!cmd->base.autoneg) {
		/* force link down */
		temp = phy_read(phydev, MII_BMCR);
		phy_write(phydev, MII_BMCR, temp | BMCR_LOOPBACK);
		mdelay(1);
		phy_write(phydev, MII_BMCR, temp);
	}

	usb_autopm_put_interface(dev->intf);

	return ret;
}