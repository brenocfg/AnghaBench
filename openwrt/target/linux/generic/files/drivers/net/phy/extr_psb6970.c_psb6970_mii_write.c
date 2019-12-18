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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {struct mii_bus* bus; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct mii_bus {int /*<<< orphan*/  (* write ) (struct mii_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PHYADDR (int) ; 
 int /*<<< orphan*/  stub1 (struct mii_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void psb6970_mii_write(struct phy_device *phydev, int reg, u16 val)
{
	struct mii_bus *bus = phydev->mdio.bus;

	bus->write(bus, PHYADDR(reg), val);
}