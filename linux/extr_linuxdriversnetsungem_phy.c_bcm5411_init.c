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
typedef  int u16 ;
struct mii_phy {int dummy; } ;

/* Variables and functions */
 int BMCR_RESET ; 
 int MII_BCM5400_GB_CONTROL ; 
 int MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP ; 
 int MII_BMCR ; 
 int /*<<< orphan*/  reset_one_mii_phy (struct mii_phy*,int) ; 
 int sungem_phy_read (struct mii_phy*,int) ; 
 int /*<<< orphan*/  sungem_phy_write (struct mii_phy*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bcm5411_init(struct mii_phy* phy)
{
	u16 data;

	/* Here's some more Apple black magic to setup
	 * some voltage stuffs.
	 */
	sungem_phy_write(phy, 0x1c, 0x8c23);
	sungem_phy_write(phy, 0x1c, 0x8ca3);
	sungem_phy_write(phy, 0x1c, 0x8c23);

	/* Here, Apple seems to want to reset it, do
	 * it as well
	 */
	sungem_phy_write(phy, MII_BMCR, BMCR_RESET);
	sungem_phy_write(phy, MII_BMCR, 0x1340);

	data = sungem_phy_read(phy, MII_BCM5400_GB_CONTROL);
	data |= MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP;
	sungem_phy_write(phy, MII_BCM5400_GB_CONTROL, data);

	udelay(10);

	/* Reset and configure cascaded 10/100 PHY */
	(void)reset_one_mii_phy(phy, 0x1f);

	return 0;
}