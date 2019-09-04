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
struct mii_phy {int autoneg; } ;

/* Variables and functions */
 int MII_NCONFIG ; 
 int /*<<< orphan*/  sungem_phy_write (struct mii_phy*,int,int) ; 

__attribute__((used)) static int bcm5421_enable_fiber(struct mii_phy* phy, int autoneg)
{
	/* enable fiber mode */
	sungem_phy_write(phy, MII_NCONFIG, 0x9020);
	/* LEDs active in both modes, autosense prio = fiber */
	sungem_phy_write(phy, MII_NCONFIG, 0x945f);

	if (!autoneg) {
		/* switch off fibre autoneg */
		sungem_phy_write(phy, MII_NCONFIG, 0xfc01);
		sungem_phy_write(phy, 0x0b, 0x0004);
	}

	phy->autoneg = autoneg;

	return 0;
}