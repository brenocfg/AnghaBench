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
typedef  int u32 ;
struct phy_setting {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct phy_device {int supported; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int SUPPORTED_Autoneg ; 
 struct phy_setting* phy_find_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void phy_sanitize_settings(struct phy_device *phydev)
{
	const struct phy_setting *setting;
	u32 features = phydev->supported;

	/* Sanitize settings based on PHY capabilities */
	if ((features & SUPPORTED_Autoneg) == 0)
		phydev->autoneg = AUTONEG_DISABLE;

	setting = phy_find_valid(phydev->speed, phydev->duplex, features);
	if (setting) {
		phydev->speed = setting->speed;
		phydev->duplex = setting->duplex;
	} else {
		/* We failed to find anything (no supported speeds?) */
		phydev->speed = SPEED_UNKNOWN;
		phydev->duplex = DUPLEX_UNKNOWN;
	}
}