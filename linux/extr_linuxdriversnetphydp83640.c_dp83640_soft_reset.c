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
 int genphy_soft_reset (struct phy_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dp83640_soft_reset(struct phy_device *phydev)
{
	int ret;

	ret = genphy_soft_reset(phydev);
	if (ret < 0)
		return ret;

	/* From DP83640 datasheet: "Software driver code must wait 3 us
	 * following a software reset before allowing further serial MII
	 * operations with the DP83640."
	 */
	udelay(10);		/* Taking udelay inaccuracy into account */

	return 0;
}