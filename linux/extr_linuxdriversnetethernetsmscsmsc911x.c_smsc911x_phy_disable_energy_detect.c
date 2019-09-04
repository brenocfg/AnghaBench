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
struct smsc911x_data {struct net_device* dev; } ;
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_LAN83C185_CTRL_STATUS ; 
 int MII_LAN83C185_EDPWRDOWN ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smsc911x_phy_disable_energy_detect(struct smsc911x_data *pdata)
{
	struct net_device *ndev = pdata->dev;
	struct phy_device *phy_dev = ndev->phydev;
	int rc = 0;

	if (!phy_dev)
		return rc;

	rc = phy_read(phy_dev, MII_LAN83C185_CTRL_STATUS);

	if (rc < 0) {
		SMSC_WARN(pdata, drv, "Failed reading PHY control reg");
		return rc;
	}

	/* Only disable if energy detect mode is already enabled */
	if (rc & MII_LAN83C185_EDPWRDOWN) {
		/* Disable energy detect mode for this SMSC Transceivers */
		rc = phy_write(phy_dev, MII_LAN83C185_CTRL_STATUS,
			       rc & (~MII_LAN83C185_EDPWRDOWN));

		if (rc < 0) {
			SMSC_WARN(pdata, drv, "Failed writing PHY control reg");
			return rc;
		}
		/* Allow PHY to wakeup */
		mdelay(2);
	}

	return 0;
}