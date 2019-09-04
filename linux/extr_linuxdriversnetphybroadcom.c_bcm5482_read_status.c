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
struct phy_device {int dev_flags; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; scalar_t__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int PHY_BCM_FLAGS_MODE_1000BX ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int genphy_read_status (struct phy_device*) ; 

__attribute__((used)) static int bcm5482_read_status(struct phy_device *phydev)
{
	int err;

	err = genphy_read_status(phydev);

	if (phydev->dev_flags & PHY_BCM_FLAGS_MODE_1000BX) {
		/*
		 * Only link status matters for 1000Base-X mode, so force
		 * 1000 Mbit/s full-duplex status
		 */
		if (phydev->link) {
			phydev->speed = SPEED_1000;
			phydev->duplex = DUPLEX_FULL;
		}
	}

	return err;
}