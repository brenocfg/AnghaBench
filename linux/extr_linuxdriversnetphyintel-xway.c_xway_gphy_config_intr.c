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
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {scalar_t__ interrupts; } ;

/* Variables and functions */
 scalar_t__ PHY_INTERRUPT_ENABLED ; 
 int /*<<< orphan*/  XWAY_MDIO_IMASK ; 
 int /*<<< orphan*/  XWAY_MDIO_INIT_MASK ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xway_gphy_config_intr(struct phy_device *phydev)
{
	u16 mask = 0;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED)
		mask = XWAY_MDIO_INIT_MASK;

	return phy_write(phydev, XWAY_MDIO_IMASK, mask);
}