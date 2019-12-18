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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ addr; struct mii_bus* bus; } ;
struct phy_device {int phy_id; TYPE_1__ mdio; } ;
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int B53_BRCM_OUI_1 ; 
 int B53_BRCM_OUI_2 ; 
 int B53_BRCM_OUI_3 ; 
 scalar_t__ B53_PSEUDO_PHY ; 
 int mdiobus_read (struct mii_bus*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int b53_phy_fixup(struct phy_device *dev)
{
	struct mii_bus *bus = dev->mdio.bus;
	u32 phy_id;

	if (dev->mdio.addr != B53_PSEUDO_PHY)
		return 0;

	/* read the first port's id */
	phy_id = mdiobus_read(bus, 0, 2) << 16;
	phy_id |= mdiobus_read(bus, 0, 3);

	if ((phy_id & 0xfffffc00) == B53_BRCM_OUI_1 ||
	    (phy_id & 0xfffffc00) == B53_BRCM_OUI_2 ||
	    (phy_id & 0xfffffc00) == B53_BRCM_OUI_3) {
		dev->phy_id = phy_id;
	}

	return 0;
}