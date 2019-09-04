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
struct phy_device {int /*<<< orphan*/  mdio; } ;
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct phy_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 struct phy_device* get_phy_device (struct mii_bus*,int,int) ; 
 int /*<<< orphan*/  of_mdiobus_link_mdiodev (struct mii_bus*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_device_free (struct phy_device*) ; 
 int phy_device_register (struct phy_device*) ; 

struct phy_device *mdiobus_scan(struct mii_bus *bus, int addr)
{
	struct phy_device *phydev;
	int err;

	phydev = get_phy_device(bus, addr, false);
	if (IS_ERR(phydev))
		return phydev;

	/*
	 * For DT, see if the auto-probed phy has a correspoding child
	 * in the bus node, and set the of_node pointer in this case.
	 */
	of_mdiobus_link_mdiodev(bus, &phydev->mdio);

	err = phy_device_register(phydev);
	if (err) {
		phy_device_free(phydev);
		return ERR_PTR(-ENODEV);
	}

	return phydev;
}