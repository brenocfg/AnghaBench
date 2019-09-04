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
struct axp20x_usb_power {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_VBUS_IPSOUT_MGMT ; 
 int /*<<< orphan*/  AXP20X_VBUS_VHOLD_MASK ; 
 int AXP20X_VBUS_VHOLD_OFFSET ; 
 int EINVAL ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int axp20x_usb_power_set_voltage_min(struct axp20x_usb_power *power,
					    int intval)
{
	int val;

	switch (intval) {
	case 4000000:
	case 4100000:
	case 4200000:
	case 4300000:
	case 4400000:
	case 4500000:
	case 4600000:
	case 4700000:
		val = (intval - 4000000) / 100000;
		return regmap_update_bits(power->regmap,
					  AXP20X_VBUS_IPSOUT_MGMT,
					  AXP20X_VBUS_VHOLD_MASK,
					  val << AXP20X_VBUS_VHOLD_OFFSET);
	default:
		return -EINVAL;
	}

	return -EINVAL;
}