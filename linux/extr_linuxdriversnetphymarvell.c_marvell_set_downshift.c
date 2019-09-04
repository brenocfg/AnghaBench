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
typedef  int u8 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_M1011_PHY_SCR ; 
 int MII_M1011_PHY_SCR_DOWNSHIFT_EN ; 
 int MII_M1011_PHY_SCR_DOWNSHIFT_SHIFT ; 
 int MII_M1011_PHY_SRC_DOWNSHIFT_MASK ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int marvell_set_downshift(struct phy_device *phydev, bool enable,
				 u8 retries)
{
	int reg;

	reg = phy_read(phydev, MII_M1011_PHY_SCR);
	if (reg < 0)
		return reg;

	reg &= MII_M1011_PHY_SRC_DOWNSHIFT_MASK;
	reg |= ((retries - 1) << MII_M1011_PHY_SCR_DOWNSHIFT_SHIFT);
	if (enable)
		reg |= MII_M1011_PHY_SCR_DOWNSHIFT_EN;

	return phy_write(phydev, MII_M1011_PHY_SCR, reg);
}