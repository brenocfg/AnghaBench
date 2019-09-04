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
struct phy_device {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  state; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_10000baseR_FEC ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  PHY_NOLINK ; 
 int /*<<< orphan*/  SUPPORTED_10000baseR_FEC ; 
 int /*<<< orphan*/  bcm87xx_of_reg_init (struct phy_device*) ; 

__attribute__((used)) static int bcm87xx_config_init(struct phy_device *phydev)
{
	phydev->supported = SUPPORTED_10000baseR_FEC;
	phydev->advertising = ADVERTISED_10000baseR_FEC;
	phydev->state = PHY_NOLINK;
	phydev->autoneg = AUTONEG_DISABLE;

	bcm87xx_of_reg_init(phydev);

	return 0;
}