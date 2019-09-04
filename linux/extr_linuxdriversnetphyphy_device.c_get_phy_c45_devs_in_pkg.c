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
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int MDIO_DEVS1 ; 
 int MDIO_DEVS2 ; 
 int MII_ADDR_C45 ; 
 int mdiobus_read (struct mii_bus*,int,int) ; 

__attribute__((used)) static int get_phy_c45_devs_in_pkg(struct mii_bus *bus, int addr, int dev_addr,
				   u32 *devices_in_package)
{
	int phy_reg, reg_addr;

	reg_addr = MII_ADDR_C45 | dev_addr << 16 | MDIO_DEVS2;
	phy_reg = mdiobus_read(bus, addr, reg_addr);
	if (phy_reg < 0)
		return -EIO;
	*devices_in_package = (phy_reg & 0xffff) << 16;

	reg_addr = MII_ADDR_C45 | dev_addr << 16 | MDIO_DEVS1;
	phy_reg = mdiobus_read(bus, addr, reg_addr);
	if (phy_reg < 0)
		return -EIO;
	*devices_in_package |= (phy_reg & 0xffff);

	return 0;
}