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
struct phy_device {int /*<<< orphan*/  attached_dev; } ;
struct lan78xx_net {int /*<<< orphan*/  interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_WIS ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII_RXID ; 
 struct lan78xx_net* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ksz9031rnx_fixup(struct phy_device *phydev)
{
	struct lan78xx_net *dev = netdev_priv(phydev->attached_dev);

	/* Micrel9301RNX PHY configuration */
	/* RGMII Control Signal Pad Skew */
	phy_write_mmd(phydev, MDIO_MMD_WIS, 4, 0x0077);
	/* RGMII RX Data Pad Skew */
	phy_write_mmd(phydev, MDIO_MMD_WIS, 5, 0x7777);
	/* RGMII RX Clock Pad Skew */
	phy_write_mmd(phydev, MDIO_MMD_WIS, 8, 0x1FF);

	dev->interface = PHY_INTERFACE_MODE_RGMII_RXID;

	return 1;
}