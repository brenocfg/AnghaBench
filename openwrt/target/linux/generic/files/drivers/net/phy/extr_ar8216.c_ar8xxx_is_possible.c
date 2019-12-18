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
typedef  int u32 ;
struct mii_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_PHYSID1 ; 
 int /*<<< orphan*/  MII_PHYSID2 ; 
 scalar_t__ ar8xxx_phy_match (int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int mdiobus_read (struct mii_bus*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static bool
ar8xxx_is_possible(struct mii_bus *bus)
{
	unsigned int i, found_phys = 0;

	for (i = 0; i < 5; i++) {
		u32 phy_id;

		phy_id = mdiobus_read(bus, i, MII_PHYSID1) << 16;
		phy_id |= mdiobus_read(bus, i, MII_PHYSID2);
		if (ar8xxx_phy_match(phy_id)) {
			found_phys++;
		} else if (phy_id) {
			pr_debug("ar8xxx: unknown PHY at %s:%02x id:%08x\n",
				 dev_name(&bus->dev), i, phy_id);
		}
	}
	return !!found_phys;
}