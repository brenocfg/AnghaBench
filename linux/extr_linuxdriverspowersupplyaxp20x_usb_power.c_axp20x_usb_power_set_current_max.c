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
struct axp20x_usb_power {int /*<<< orphan*/  regmap; int /*<<< orphan*/  axp20x_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_VBUS_CLIMIT_MASK ; 
 int /*<<< orphan*/  AXP20X_VBUS_IPSOUT_MGMT ; 
 int /*<<< orphan*/  AXP221_ID ; 
 int EINVAL ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int axp20x_usb_power_set_current_max(struct axp20x_usb_power *power,
					    int intval)
{
	int val;

	switch (intval) {
	case 100000:
		if (power->axp20x_id == AXP221_ID)
			return -EINVAL;
		/* fall through */
	case 500000:
	case 900000:
		val = (900000 - intval) / 400000;
		return regmap_update_bits(power->regmap,
					  AXP20X_VBUS_IPSOUT_MGMT,
					  AXP20X_VBUS_CLIMIT_MASK, val);
	default:
		return -EINVAL;
	}

	return -EINVAL;
}