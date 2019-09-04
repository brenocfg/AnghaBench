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
 int /*<<< orphan*/  MII_M1011_PHY_STATUS ; 
 int MII_M1011_PHY_STATUS_RESOLVED ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_aneg_done(struct phy_device *phydev)
{
	int retval = phy_read(phydev, MII_M1011_PHY_STATUS);

	return (retval < 0) ? retval : (retval & MII_M1011_PHY_STATUS_RESOLVED);
}