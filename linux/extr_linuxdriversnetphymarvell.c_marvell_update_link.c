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
struct phy_device {int link; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_M1011_PHY_STATUS ; 
 int REGISTER_LINK_STATUS ; 
 int genphy_update_link (struct phy_device*) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_update_link(struct phy_device *phydev, int fiber)
{
	int status;

	/* Use the generic register for copper link, or specific
	 * register for fiber case
	 */
	if (fiber) {
		status = phy_read(phydev, MII_M1011_PHY_STATUS);
		if (status < 0)
			return status;

		if ((status & REGISTER_LINK_STATUS) == 0)
			phydev->link = 0;
		else
			phydev->link = 1;
	} else {
		return genphy_update_link(phydev);
	}

	return 0;
}