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
struct phy_device {int dev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM54810_SHD_CLK_CTL ; 
 int BCM54810_SHD_CLK_CTL_GTXCLK_EN ; 
 int CTL1000_AS_MASTER ; 
 int CTL1000_ENABLE_MASTER ; 
 int MII_BCM54XX_AUXCTL_MISC_WREN ; 
 int /*<<< orphan*/  MII_BCM54XX_AUXCTL_SHDWSEL_MISC ; 
 int MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_SKEW_EN ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int PHY_BRCM_EN_MASTER_MODE ; 
 int bcm54xx_auxctl_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm54xx_auxctl_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int bcm_phy_read_shadow (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_phy_write_shadow (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm54210e_config_init(struct phy_device *phydev)
{
	int val;

	val = bcm54xx_auxctl_read(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC);
	val &= ~MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_SKEW_EN;
	val |= MII_BCM54XX_AUXCTL_MISC_WREN;
	bcm54xx_auxctl_write(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC, val);

	val = bcm_phy_read_shadow(phydev, BCM54810_SHD_CLK_CTL);
	val &= ~BCM54810_SHD_CLK_CTL_GTXCLK_EN;
	bcm_phy_write_shadow(phydev, BCM54810_SHD_CLK_CTL, val);

	if (phydev->dev_flags & PHY_BRCM_EN_MASTER_MODE) {
		val = phy_read(phydev, MII_CTRL1000);
		val |= CTL1000_AS_MASTER | CTL1000_ENABLE_MASTER;
		phy_write(phydev, MII_CTRL1000, val);
	}

	return 0;
}