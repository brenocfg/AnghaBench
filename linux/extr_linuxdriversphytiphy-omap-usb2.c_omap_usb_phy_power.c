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
typedef  int /*<<< orphan*/  u32 ;
struct omap_usb {int /*<<< orphan*/  mask; int /*<<< orphan*/  power_reg; int /*<<< orphan*/  syscon_phy_power; int /*<<< orphan*/  power_off; int /*<<< orphan*/  power_on; int /*<<< orphan*/  control_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_control_phy_power (int /*<<< orphan*/ ,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_usb_phy_power(struct omap_usb *phy, int on)
{
	u32 val;
	int ret;

	if (!phy->syscon_phy_power) {
		omap_control_phy_power(phy->control_dev, on);
		return 0;
	}

	if (on)
		val = phy->power_on;
	else
		val = phy->power_off;

	ret = regmap_update_bits(phy->syscon_phy_power, phy->power_reg,
				 phy->mask, val);
	return ret;
}