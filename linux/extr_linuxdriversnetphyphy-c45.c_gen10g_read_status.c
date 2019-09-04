#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int devices_in_package; } ;
struct phy_device {int link; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; TYPE_1__ c45_ids; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 int /*<<< orphan*/  MDIO_MMD_VEND2 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int genphy_c45_read_link (struct phy_device*,int) ; 

int gen10g_read_status(struct phy_device *phydev)
{
	u32 mmd_mask = phydev->c45_ids.devices_in_package;
	int ret;

	/* For now just lie and say it's 10G all the time */
	phydev->speed = SPEED_10000;
	phydev->duplex = DUPLEX_FULL;

	/* Avoid reading the vendor MMDs */
	mmd_mask &= ~(BIT(MDIO_MMD_VEND1) | BIT(MDIO_MMD_VEND2));

	ret = genphy_c45_read_link(phydev, mmd_mask);

	phydev->link = ret > 0 ? 1 : 0;

	return 0;
}