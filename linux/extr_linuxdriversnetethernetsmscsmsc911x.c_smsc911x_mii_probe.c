#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  phy_interface; } ;
struct smsc911x_data {int last_duplex; int last_carrier; TYPE_2__ config; int /*<<< orphan*/  mii_bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct phy_device {int supported; int advertising; int /*<<< orphan*/  phy_id; TYPE_1__ mdio; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int PHY_BASIC_FEATURES ; 
 int /*<<< orphan*/  SMSC_TRACE (struct smsc911x_data*,int /*<<< orphan*/ ,char*,...) ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Pause ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 int phy_connect_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  smsc911x_phy_adjust_link ; 

__attribute__((used)) static int smsc911x_mii_probe(struct net_device *dev)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	struct phy_device *phydev = NULL;
	int ret;

	/* find the first phy */
	phydev = phy_find_first(pdata->mii_bus);
	if (!phydev) {
		netdev_err(dev, "no PHY found\n");
		return -ENODEV;
	}

	SMSC_TRACE(pdata, probe, "PHY: addr %d, phy_id 0x%08X",
		   phydev->mdio.addr, phydev->phy_id);

	ret = phy_connect_direct(dev, phydev, &smsc911x_phy_adjust_link,
				 pdata->config.phy_interface);

	if (ret) {
		netdev_err(dev, "Could not attach to PHY\n");
		return ret;
	}

	phy_attached_info(phydev);

	/* mask with MAC supported features */
	phydev->supported &= (PHY_BASIC_FEATURES | SUPPORTED_Pause |
			      SUPPORTED_Asym_Pause);
	phydev->advertising = phydev->supported;

	pdata->last_duplex = -1;
	pdata->last_carrier = -1;

#ifdef USE_PHY_WORK_AROUND
	if (smsc911x_phy_loopbacktest(dev) < 0) {
		SMSC_WARN(pdata, hw, "Failed Loop Back Test");
		phy_disconnect(phydev);
		return -ENODEV;
	}
	SMSC_TRACE(pdata, hw, "Passed Loop Back Test");
#endif				/* USE_PHY_WORK_AROUND */

	SMSC_TRACE(pdata, hw, "phy initialised successfully");
	return 0;
}