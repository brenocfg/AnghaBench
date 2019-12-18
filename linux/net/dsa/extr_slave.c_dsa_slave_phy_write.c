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
struct mii_bus {struct dsa_switch* priv; } ;
struct dsa_switch {int phys_mii_mask; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* phy_write ) (struct dsa_switch*,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct dsa_switch*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_slave_phy_write(struct mii_bus *bus, int addr, int reg, u16 val)
{
	struct dsa_switch *ds = bus->priv;

	if (ds->phys_mii_mask & (1 << addr))
		return ds->ops->phy_write(ds, addr, reg, val);

	return 0;
}