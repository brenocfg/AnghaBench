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
 int bcm7xxx_28nm_config_init (struct phy_device*) ; 
 int genphy_config_aneg (struct phy_device*) ; 

__attribute__((used)) static int bcm7xxx_28nm_resume(struct phy_device *phydev)
{
	int ret;

	/* Re-apply workarounds coming out suspend/resume */
	ret = bcm7xxx_28nm_config_init(phydev);
	if (ret)
		return ret;

	/* 28nm Gigabit PHYs come out of reset without any half-duplex
	 * or "hub" compliant advertised mode, fix that. This does not
	 * cause any problems with the PHY library since genphy_config_aneg()
	 * gracefully handles auto-negotiated and forced modes.
	 */
	return genphy_config_aneg(phydev);
}