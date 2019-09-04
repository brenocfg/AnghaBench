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
struct phy_device {int /*<<< orphan*/  supported; int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_AQUANTIA_FEATURES ; 

__attribute__((used)) static int aquantia_config_aneg(struct phy_device *phydev)
{
	phydev->supported = PHY_AQUANTIA_FEATURES;
	phydev->advertising = phydev->supported;

	return 0;
}