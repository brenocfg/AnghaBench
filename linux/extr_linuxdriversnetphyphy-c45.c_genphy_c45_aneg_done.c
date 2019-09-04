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
 int MDIO_AN_STAT1_COMPLETE ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int genphy_c45_aneg_done(struct phy_device *phydev)
{
	int val = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);

	return val < 0 ? val : val & MDIO_AN_STAT1_COMPLETE ? 1 : 0;
}