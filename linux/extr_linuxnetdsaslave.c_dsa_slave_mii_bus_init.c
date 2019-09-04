#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dsa_switch {int index; int /*<<< orphan*/  phys_mii_mask; TYPE_2__* slave_mii_bus; int /*<<< orphan*/  dev; TYPE_1__* dst; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  phy_mask; int /*<<< orphan*/  parent; int /*<<< orphan*/  id; int /*<<< orphan*/  write; int /*<<< orphan*/  read; void* priv; } ;
struct TYPE_3__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  dsa_slave_phy_read ; 
 int /*<<< orphan*/  dsa_slave_phy_write ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

void dsa_slave_mii_bus_init(struct dsa_switch *ds)
{
	ds->slave_mii_bus->priv = (void *)ds;
	ds->slave_mii_bus->name = "dsa slave smi";
	ds->slave_mii_bus->read = dsa_slave_phy_read;
	ds->slave_mii_bus->write = dsa_slave_phy_write;
	snprintf(ds->slave_mii_bus->id, MII_BUS_ID_SIZE, "dsa-%d.%d",
		 ds->dst->index, ds->index);
	ds->slave_mii_bus->parent = ds->dev;
	ds->slave_mii_bus->phy_mask = ~ds->phys_mii_mask;
}