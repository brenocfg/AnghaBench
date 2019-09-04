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
struct phy_device {scalar_t__ interface; int dev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM54612E_EXP_SPARE0 ; 
 int BCM54612E_LED4_CLK125OUT_EN ; 
 int MII_BCM54XX_AUXCTL_MISC_WREN ; 
 int MII_BCM54XX_AUXCTL_SHDWSEL_MASK ; 
 int /*<<< orphan*/  MII_BCM54XX_AUXCTL_SHDWSEL_MISC ; 
 int MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_SKEW_EN ; 
 int PHY_BRCM_RX_REFCLK_UNUSED ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_RXID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_TXID ; 
 int bcm54xx_auxctl_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm54xx_auxctl_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int bcm_phy_read_exp (struct phy_device*,int /*<<< orphan*/ ) ; 
 int bcm_phy_write_exp (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm_phy_write_shadow (struct phy_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm54612e_config_init(struct phy_device *phydev)
{
	int reg;

	/* Clear TX internal delay unless requested. */
	if ((phydev->interface != PHY_INTERFACE_MODE_RGMII_ID) &&
	    (phydev->interface != PHY_INTERFACE_MODE_RGMII_TXID)) {
		/* Disable TXD to GTXCLK clock delay (default set) */
		/* Bit 9 is the only field in shadow register 00011 */
		bcm_phy_write_shadow(phydev, 0x03, 0);
	}

	/* Clear RX internal delay unless requested. */
	if ((phydev->interface != PHY_INTERFACE_MODE_RGMII_ID) &&
	    (phydev->interface != PHY_INTERFACE_MODE_RGMII_RXID)) {
		reg = bcm54xx_auxctl_read(phydev,
					  MII_BCM54XX_AUXCTL_SHDWSEL_MISC);
		/* Disable RXD to RXC delay (default set) */
		reg &= ~MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_SKEW_EN;
		/* Clear shadow selector field */
		reg &= ~MII_BCM54XX_AUXCTL_SHDWSEL_MASK;
		bcm54xx_auxctl_write(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC,
				     MII_BCM54XX_AUXCTL_MISC_WREN | reg);
	}

	/* Enable CLK125 MUX on LED4 if ref clock is enabled. */
	if (!(phydev->dev_flags & PHY_BRCM_RX_REFCLK_UNUSED)) {
		int err;

		reg = bcm_phy_read_exp(phydev, BCM54612E_EXP_SPARE0);
		err = bcm_phy_write_exp(phydev, BCM54612E_EXP_SPARE0,
					BCM54612E_LED4_CLK125OUT_EN | reg);

		if (err < 0)
			return err;
	}

	return 0;
}