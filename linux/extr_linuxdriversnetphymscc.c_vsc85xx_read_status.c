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
struct phy_device {int /*<<< orphan*/  mdix; } ;

/* Variables and functions */
 int genphy_read_status (struct phy_device*) ; 
 int vsc85xx_mdix_get (struct phy_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vsc85xx_read_status(struct phy_device *phydev)
{
	int rc;

	rc = vsc85xx_mdix_get(phydev, &phydev->mdix);
	if (rc < 0)
		return rc;

	return genphy_read_status(phydev);
}