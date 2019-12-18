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
struct mii_bus {struct ag71xx_mdio* priv; } ;
struct ag71xx_mdio {TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ builtin_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ag71xx_mdio_mii_write (struct ag71xx_mdio*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar7240sw_phy_write (struct mii_bus*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ag71xx_mdio_write(struct mii_bus *bus, int addr, int reg, u16 val)
{
	struct ag71xx_mdio *am = bus->priv;

	if (am->pdata->builtin_switch)
		ar7240sw_phy_write(bus, addr, reg, val);
	else
		ag71xx_mdio_mii_write(am, addr, reg, val);
	return 0;
}