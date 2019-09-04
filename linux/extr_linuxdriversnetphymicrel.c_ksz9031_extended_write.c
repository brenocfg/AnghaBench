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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_KSZ9031RN_MMD_CTRL_REG ; 
 int /*<<< orphan*/  MII_KSZ9031RN_MMD_REGDATA_REG ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ksz9031_extended_write(struct phy_device *phydev,
				  u8 mode, u32 dev_addr, u32 regnum, u16 val)
{
	phy_write(phydev, MII_KSZ9031RN_MMD_CTRL_REG, dev_addr);
	phy_write(phydev, MII_KSZ9031RN_MMD_REGDATA_REG, regnum);
	phy_write(phydev, MII_KSZ9031RN_MMD_CTRL_REG, (mode << 14) | dev_addr);
	return phy_write(phydev, MII_KSZ9031RN_MMD_REGDATA_REG, val);
}