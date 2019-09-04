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
struct phy_device {int dev_flags; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int MICREL_PHY_FXEN ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int genphy_config_aneg (struct phy_device*) ; 

__attribute__((used)) static int ksz8041_config_aneg(struct phy_device *phydev)
{
	/* Skip auto-negotiation in fiber mode */
	if (phydev->dev_flags & MICREL_PHY_FXEN) {
		phydev->speed = SPEED_100;
		return 0;
	}

	return genphy_config_aneg(phydev);
}