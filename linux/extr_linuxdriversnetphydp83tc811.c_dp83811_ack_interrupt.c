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
 int /*<<< orphan*/  MII_DP83811_INT_STAT1 ; 
 int /*<<< orphan*/  MII_DP83811_INT_STAT2 ; 
 int /*<<< orphan*/  MII_DP83811_INT_STAT3 ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dp83811_ack_interrupt(struct phy_device *phydev)
{
	int err;

	err = phy_read(phydev, MII_DP83811_INT_STAT1);
	if (err < 0)
		return err;

	err = phy_read(phydev, MII_DP83811_INT_STAT2);
	if (err < 0)
		return err;

	err = phy_read(phydev, MII_DP83811_INT_STAT3);
	if (err < 0)
		return err;

	return 0;
}