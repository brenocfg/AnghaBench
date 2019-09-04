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
typedef  int /*<<< orphan*/  u16 ;
struct mii_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_BCM5201_MULTIPHY ; 
 int /*<<< orphan*/  MII_BCM5201_MULTIPHY_SERIALMODE ; 
 int /*<<< orphan*/  MII_BCM5400_AUXCONTROL ; 
 int /*<<< orphan*/  MII_BCM5400_AUXCONTROL_PWR10BASET ; 
 int /*<<< orphan*/  MII_BCM5400_GB_CONTROL ; 
 int /*<<< orphan*/  MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP ; 
 int /*<<< orphan*/  __sungem_phy_read (struct mii_phy*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sungem_phy_write (struct mii_phy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_one_mii_phy (struct mii_phy*,int) ; 
 int /*<<< orphan*/  sungem_phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sungem_phy_write (struct mii_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bcm5400_init(struct mii_phy* phy)
{
	u16 data;

	/* Configure for gigabit full duplex */
	data = sungem_phy_read(phy, MII_BCM5400_AUXCONTROL);
	data |= MII_BCM5400_AUXCONTROL_PWR10BASET;
	sungem_phy_write(phy, MII_BCM5400_AUXCONTROL, data);

	data = sungem_phy_read(phy, MII_BCM5400_GB_CONTROL);
	data |= MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP;
	sungem_phy_write(phy, MII_BCM5400_GB_CONTROL, data);

	udelay(100);

	/* Reset and configure cascaded 10/100 PHY */
	(void)reset_one_mii_phy(phy, 0x1f);

	data = __sungem_phy_read(phy, 0x1f, MII_BCM5201_MULTIPHY);
	data |= MII_BCM5201_MULTIPHY_SERIALMODE;
	__sungem_phy_write(phy, 0x1f, MII_BCM5201_MULTIPHY, data);

	data = sungem_phy_read(phy, MII_BCM5400_AUXCONTROL);
	data &= ~MII_BCM5400_AUXCONTROL_PWR10BASET;
	sungem_phy_write(phy, MII_BCM5400_AUXCONTROL, data);

	return 0;
}