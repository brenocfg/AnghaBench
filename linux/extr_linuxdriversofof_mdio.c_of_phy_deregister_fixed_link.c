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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_phy_unregister (struct phy_device*) ; 
 struct phy_device* of_phy_find_device (struct device_node*) ; 
 int /*<<< orphan*/  phy_device_free (struct phy_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void of_phy_deregister_fixed_link(struct device_node *np)
{
	struct phy_device *phydev;

	phydev = of_phy_find_device(np);
	if (!phydev)
		return;

	fixed_phy_unregister(phydev);

	put_device(&phydev->mdio.dev);	/* of_phy_find_device() */
	phy_device_free(phydev);	/* fixed_phy_register() */
}