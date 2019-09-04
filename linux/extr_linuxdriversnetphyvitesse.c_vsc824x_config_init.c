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
struct phy_device {scalar_t__ interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_VSC8244_AUXCONSTAT_INIT ; 
 int /*<<< orphan*/  MII_VSC8244_AUX_CONSTAT ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vsc824x_add_skew (struct phy_device*) ; 

__attribute__((used)) static int vsc824x_config_init(struct phy_device *phydev)
{
	int err;

	err = phy_write(phydev, MII_VSC8244_AUX_CONSTAT,
			MII_VSC8244_AUXCONSTAT_INIT);
	if (err < 0)
		return err;

	if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID)
		err = vsc824x_add_skew(phydev);

	return err;
}