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
typedef  int u16 ;
struct mii_bus {int /*<<< orphan*/  (* write ) (struct mii_bus*,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MII_ATH_MMD_ADDR ; 
 int /*<<< orphan*/  MII_ATH_MMD_DATA ; 
 int /*<<< orphan*/  stub1 (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
ar8xxx_phy_mmd_prep(struct mii_bus *bus, int phy_addr, u16 addr, u16 reg)
{
	bus->write(bus, phy_addr, MII_ATH_MMD_ADDR, addr);
	bus->write(bus, phy_addr, MII_ATH_MMD_DATA, reg);
	bus->write(bus, phy_addr, MII_ATH_MMD_ADDR, addr | 0x4000);
}