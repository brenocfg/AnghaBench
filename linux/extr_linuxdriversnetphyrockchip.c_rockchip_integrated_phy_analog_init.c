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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMI_ADDR_TSTCNTL ; 
 int /*<<< orphan*/  SMI_ADDR_TSTWRITE ; 
 int TSTCNTL_WR ; 
 int WR_ADDR_A7CFG ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int rockchip_close_tstmode (struct phy_device*) ; 
 int rockchip_init_tstmode (struct phy_device*) ; 

__attribute__((used)) static int rockchip_integrated_phy_analog_init(struct phy_device *phydev)
{
	int ret;

	ret = rockchip_init_tstmode(phydev);
	if (ret)
		return ret;

	/*
	 * Adjust tx amplitude to make sginal better,
	 * the default value is 0x8.
	 */
	ret = phy_write(phydev, SMI_ADDR_TSTWRITE, 0xB);
	if (ret)
		return ret;
	ret = phy_write(phydev, SMI_ADDR_TSTCNTL, TSTCNTL_WR | WR_ADDR_A7CFG);
	if (ret)
		return ret;

	return rockchip_close_tstmode(phydev);
}