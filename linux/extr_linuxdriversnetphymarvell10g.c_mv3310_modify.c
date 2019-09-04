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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int phy_read_mmd (struct phy_device*,int,int) ; 
 int phy_write_mmd (struct phy_device*,int,int,int) ; 

__attribute__((used)) static int mv3310_modify(struct phy_device *phydev, int devad, u16 reg,
			 u16 mask, u16 bits)
{
	int old, val, ret;

	old = phy_read_mmd(phydev, devad, reg);
	if (old < 0)
		return old;

	val = (old & ~mask) | (bits & mask);
	if (val == old)
		return 0;

	ret = phy_write_mmd(phydev, devad, reg, val);

	return ret < 0 ? ret : 1;
}