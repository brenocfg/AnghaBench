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
typedef  int u32 ;
struct phy_device {int dev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM54XX_SHD_APD ; 
 int BCM54XX_SHD_APD_EN ; 
 int /*<<< orphan*/  BCM54XX_SHD_SCR3 ; 
 int BCM54XX_SHD_SCR3_DEF_CLK125 ; 
 int BCM54XX_SHD_SCR3_DLLAPD_DIS ; 
 int BCM54XX_SHD_SCR3_TRDDAPD ; 
 scalar_t__ BRCM_PHY_MODEL (struct phy_device*) ; 
 int BRCM_PHY_REV (struct phy_device*) ; 
 int PHY_BRCM_AUTO_PWRDWN_ENABLE ; 
 int PHY_BRCM_DIS_TXCRXC_NOENRGY ; 
 int PHY_BRCM_RX_REFCLK_UNUSED ; 
 scalar_t__ PHY_ID_BCM50610 ; 
 scalar_t__ PHY_ID_BCM50610M ; 
 scalar_t__ PHY_ID_BCM57780 ; 
 int bcm_phy_read_shadow (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_phy_write_shadow (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcm54xx_adjust_rxrefclk(struct phy_device *phydev)
{
	u32 orig;
	int val;
	bool clk125en = true;

	/* Abort if we are using an untested phy. */
	if (BRCM_PHY_MODEL(phydev) != PHY_ID_BCM57780 &&
	    BRCM_PHY_MODEL(phydev) != PHY_ID_BCM50610 &&
	    BRCM_PHY_MODEL(phydev) != PHY_ID_BCM50610M)
		return;

	val = bcm_phy_read_shadow(phydev, BCM54XX_SHD_SCR3);
	if (val < 0)
		return;

	orig = val;

	if ((BRCM_PHY_MODEL(phydev) == PHY_ID_BCM50610 ||
	     BRCM_PHY_MODEL(phydev) == PHY_ID_BCM50610M) &&
	    BRCM_PHY_REV(phydev) >= 0x3) {
		/*
		 * Here, bit 0 _disables_ CLK125 when set.
		 * This bit is set by default.
		 */
		clk125en = false;
	} else {
		if (phydev->dev_flags & PHY_BRCM_RX_REFCLK_UNUSED) {
			/* Here, bit 0 _enables_ CLK125 when set */
			val &= ~BCM54XX_SHD_SCR3_DEF_CLK125;
			clk125en = false;
		}
	}

	if (!clk125en || (phydev->dev_flags & PHY_BRCM_AUTO_PWRDWN_ENABLE))
		val &= ~BCM54XX_SHD_SCR3_DLLAPD_DIS;
	else
		val |= BCM54XX_SHD_SCR3_DLLAPD_DIS;

	if (phydev->dev_flags & PHY_BRCM_DIS_TXCRXC_NOENRGY)
		val |= BCM54XX_SHD_SCR3_TRDDAPD;

	if (orig != val)
		bcm_phy_write_shadow(phydev, BCM54XX_SHD_SCR3, val);

	val = bcm_phy_read_shadow(phydev, BCM54XX_SHD_APD);
	if (val < 0)
		return;

	orig = val;

	if (!clk125en || (phydev->dev_flags & PHY_BRCM_AUTO_PWRDWN_ENABLE))
		val |= BCM54XX_SHD_APD_EN;
	else
		val &= ~BCM54XX_SHD_APD_EN;

	if (orig != val)
		bcm_phy_write_shadow(phydev, BCM54XX_SHD_APD, val);
}