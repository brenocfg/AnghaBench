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
struct smsc_phy_priv {scalar_t__ energy_enable; } ;
struct phy_device {int /*<<< orphan*/  link; struct smsc_phy_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_LAN83C185_CTRL_STATUS ; 
 int MII_LAN83C185_EDPWRDOWN ; 
 int MII_LAN83C185_ENERGYON ; 
 int genphy_read_status (struct phy_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan87xx_read_status(struct phy_device *phydev)
{
	struct smsc_phy_priv *priv = phydev->priv;

	int err = genphy_read_status(phydev);

	if (!phydev->link && priv->energy_enable) {
		int i;

		/* Disable EDPD to wake up PHY */
		int rc = phy_read(phydev, MII_LAN83C185_CTRL_STATUS);
		if (rc < 0)
			return rc;

		rc = phy_write(phydev, MII_LAN83C185_CTRL_STATUS,
			       rc & ~MII_LAN83C185_EDPWRDOWN);
		if (rc < 0)
			return rc;

		/* Wait max 640 ms to detect energy */
		for (i = 0; i < 64; i++) {
			/* Sleep to allow link test pulses to be sent */
			msleep(10);
			rc = phy_read(phydev, MII_LAN83C185_CTRL_STATUS);
			if (rc < 0)
				return rc;
			if (rc & MII_LAN83C185_ENERGYON)
				break;
		}

		/* Re-enable EDPD */
		rc = phy_read(phydev, MII_LAN83C185_CTRL_STATUS);
		if (rc < 0)
			return rc;

		rc = phy_write(phydev, MII_LAN83C185_CTRL_STATUS,
			       rc | MII_LAN83C185_EDPWRDOWN);
		if (rc < 0)
			return rc;
	}

	return err;
}