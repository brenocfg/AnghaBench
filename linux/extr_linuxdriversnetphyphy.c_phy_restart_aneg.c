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
struct TYPE_2__ {int devices_in_package; } ;
struct phy_device {TYPE_1__ c45_ids; scalar_t__ is_c45; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int genphy_c45_restart_aneg (struct phy_device*) ; 
 int genphy_restart_aneg (struct phy_device*) ; 

int phy_restart_aneg(struct phy_device *phydev)
{
	int ret;

	if (phydev->is_c45 && !(phydev->c45_ids.devices_in_package & BIT(0)))
		ret = genphy_c45_restart_aneg(phydev);
	else
		ret = genphy_restart_aneg(phydev);

	return ret;
}