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
typedef  int u16 ;
struct phy_device {scalar_t__ interrupts; TYPE_1__* drv; } ;
struct kszphy_type {int interrupt_level_mask; } ;
struct TYPE_2__ {struct kszphy_type* driver_data; } ;

/* Variables and functions */
 int KSZPHY_CTRL_INT_ACTIVE_HIGH ; 
 int KSZPHY_INTCS_ALL ; 
 int /*<<< orphan*/  MII_KSZPHY_CTRL ; 
 int /*<<< orphan*/  MII_KSZPHY_INTCS ; 
 scalar_t__ PHY_INTERRUPT_ENABLED ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kszphy_config_intr(struct phy_device *phydev)
{
	const struct kszphy_type *type = phydev->drv->driver_data;
	int temp;
	u16 mask;

	if (type && type->interrupt_level_mask)
		mask = type->interrupt_level_mask;
	else
		mask = KSZPHY_CTRL_INT_ACTIVE_HIGH;

	/* set the interrupt pin active low */
	temp = phy_read(phydev, MII_KSZPHY_CTRL);
	if (temp < 0)
		return temp;
	temp &= ~mask;
	phy_write(phydev, MII_KSZPHY_CTRL, temp);

	/* enable / disable interrupts */
	if (phydev->interrupts == PHY_INTERRUPT_ENABLED)
		temp = KSZPHY_INTCS_ALL;
	else
		temp = 0;

	return phy_write(phydev, MII_KSZPHY_INTCS, temp);
}