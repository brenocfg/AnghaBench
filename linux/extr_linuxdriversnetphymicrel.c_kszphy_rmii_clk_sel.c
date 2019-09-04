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
 int KSZPHY_RMII_REF_CLK_SEL ; 
 int /*<<< orphan*/  MII_KSZPHY_CTRL ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kszphy_rmii_clk_sel(struct phy_device *phydev, bool val)
{
	int ctrl;

	ctrl = phy_read(phydev, MII_KSZPHY_CTRL);
	if (ctrl < 0)
		return ctrl;

	if (val)
		ctrl |= KSZPHY_RMII_REF_CLK_SEL;
	else
		ctrl &= ~KSZPHY_RMII_REF_CLK_SEL;

	return phy_write(phydev, MII_KSZPHY_CTRL, ctrl);
}