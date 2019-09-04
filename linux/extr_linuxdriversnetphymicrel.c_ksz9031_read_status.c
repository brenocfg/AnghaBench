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
struct phy_device {TYPE_1__* drv; scalar_t__ link; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* config_intr ) (struct phy_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MII_STAT1000 ; 
 int genphy_config_aneg (struct phy_device*) ; 
 int genphy_read_status (struct phy_device*) ; 
 int /*<<< orphan*/  phy_init_hw (struct phy_device*) ; 
 scalar_t__ phy_interrupt_is_valid (struct phy_device*) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct phy_device*) ; 

__attribute__((used)) static int ksz9031_read_status(struct phy_device *phydev)
{
	int err;
	int regval;

	err = genphy_read_status(phydev);
	if (err)
		return err;

	/* Make sure the PHY is not broken. Read idle error count,
	 * and reset the PHY if it is maxed out.
	 */
	regval = phy_read(phydev, MII_STAT1000);
	if ((regval & 0xFF) == 0xFF) {
		phy_init_hw(phydev);
		phydev->link = 0;
		if (phydev->drv->config_intr && phy_interrupt_is_valid(phydev))
			phydev->drv->config_intr(phydev);
		return genphy_config_aneg(phydev);
	}

	return 0;
}