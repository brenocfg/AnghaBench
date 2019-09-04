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
struct phy_device {int dummy; } ;

/* Variables and functions */
#define  ETH_TP_MDI 131 
#define  ETH_TP_MDI_AUTO 130 
#define  ETH_TP_MDI_INVALID 129 
#define  ETH_TP_MDI_X 128 
 int MII_AUTO_MDIX_EN ; 
 int /*<<< orphan*/  MII_INTERNAL_CTRL_STATUS ; 
 int MII_MDIX_EN ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rockchip_set_polarity(struct phy_device *phydev, int polarity)
{
	int reg, err, val;

	/* get the current settings */
	reg = phy_read(phydev, MII_INTERNAL_CTRL_STATUS);
	if (reg < 0)
		return reg;

	reg &= ~MII_AUTO_MDIX_EN;
	val = reg;
	switch (polarity) {
	case ETH_TP_MDI:
		val &= ~MII_MDIX_EN;
		break;
	case ETH_TP_MDI_X:
		val |= MII_MDIX_EN;
		break;
	case ETH_TP_MDI_AUTO:
	case ETH_TP_MDI_INVALID:
	default:
		return 0;
	}

	if (val != reg) {
		/* Set the new polarity value in the register */
		err = phy_write(phydev, MII_INTERNAL_CTRL_STATUS, val);
		if (err)
			return err;
	}

	return 0;
}