#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct phy_device {TYPE_1__ mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdiobus_unregister_device (TYPE_1__*) ; 
 int /*<<< orphan*/  phy_device_reset (struct phy_device*,int) ; 

void phy_device_remove(struct phy_device *phydev)
{
	device_del(&phydev->mdio.dev);

	/* Assert the reset signal */
	phy_device_reset(phydev, 1);

	mdiobus_unregister_device(&phydev->mdio);
}