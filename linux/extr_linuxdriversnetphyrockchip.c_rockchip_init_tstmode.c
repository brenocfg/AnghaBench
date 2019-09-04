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
 int /*<<< orphan*/  TSTMODE_DISABLE ; 
 int /*<<< orphan*/  TSTMODE_ENABLE ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_init_tstmode(struct phy_device *phydev)
{
	int ret;

	/* Enable access to Analog and DSP register banks */
	ret = phy_write(phydev, SMI_ADDR_TSTCNTL, TSTMODE_ENABLE);
	if (ret)
		return ret;

	ret = phy_write(phydev, SMI_ADDR_TSTCNTL, TSTMODE_DISABLE);
	if (ret)
		return ret;

	return phy_write(phydev, SMI_ADDR_TSTCNTL, TSTMODE_ENABLE);
}