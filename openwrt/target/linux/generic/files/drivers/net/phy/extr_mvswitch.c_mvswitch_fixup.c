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
struct TYPE_2__ {int addr; struct mii_bus* bus; } ;
struct phy_device {int /*<<< orphan*/  phy_id; TYPE_1__ mdio; } ;
struct mii_bus {int (* read ) (struct mii_bus*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IDENT ; 
 int /*<<< orphan*/  MVSWITCH_MAGIC ; 
 int MV_IDENT_MASK ; 
 int MV_IDENT_VALUE ; 
 int /*<<< orphan*/  MV_PORTREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct mii_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mvswitch_fixup(struct phy_device *dev)
{
	struct mii_bus *bus = dev->mdio.bus;
	u16 reg;

	if (dev->mdio.addr != 0x10)
		return 0;

	reg = bus->read(bus, MV_PORTREG(IDENT, 0)) & MV_IDENT_MASK;
	if (reg != MV_IDENT_VALUE)
		return 0;

	dev->phy_id = MVSWITCH_MAGIC;
	return 0;
}