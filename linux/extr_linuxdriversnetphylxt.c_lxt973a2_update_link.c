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
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lxt973a2_update_link(struct phy_device *phydev)
{
	int status;
	int control;
	int retry = 8; /* we try 8 times */

	/* Do a fake read */
	status = phy_read(phydev, MII_BMSR);

	if (status < 0)
		return status;

	control = phy_read(phydev, MII_BMCR);
	if (control < 0)
		return control;

	do {
		/* Read link and autonegotiation status */
		status = phy_read(phydev, MII_BMSR);
	} while (status >= 0 && retry-- && status == control);

	if (status < 0)
		return status;

	if ((status & BMSR_LSTATUS) == 0)
		phydev->link = 0;
	else
		phydev->link = 1;

	return 0;
}