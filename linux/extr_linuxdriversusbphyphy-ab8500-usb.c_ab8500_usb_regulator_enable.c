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
struct ab8500_usb {int flags; scalar_t__ saved_v_ulpi; int /*<<< orphan*/  dev; int /*<<< orphan*/  v_musb; int /*<<< orphan*/  v_ulpi; int /*<<< orphan*/  v_ape; } ;

/* Variables and functions */
 int AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 void* regulator_get_voltage (int /*<<< orphan*/ ) ; 
 int regulator_set_load (int /*<<< orphan*/ ,int) ; 
 int regulator_set_voltage (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ab8500_usb_regulator_enable(struct ab8500_usb *ab)
{
	int ret, volt;

	ret = regulator_enable(ab->v_ape);
	if (ret)
		dev_err(ab->dev, "Failed to enable v-ape\n");

	if (ab->flags & AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE) {
		ab->saved_v_ulpi = regulator_get_voltage(ab->v_ulpi);
		if (ab->saved_v_ulpi < 0)
			dev_err(ab->dev, "Failed to get v_ulpi voltage\n");

		ret = regulator_set_voltage(ab->v_ulpi, 1300000, 1350000);
		if (ret < 0)
			dev_err(ab->dev, "Failed to set the Vintcore to 1.3V, ret=%d\n",
					ret);

		ret = regulator_set_load(ab->v_ulpi, 28000);
		if (ret < 0)
			dev_err(ab->dev, "Failed to set optimum mode (ret=%d)\n",
					ret);
	}

	ret = regulator_enable(ab->v_ulpi);
	if (ret)
		dev_err(ab->dev, "Failed to enable vddulpivio18\n");

	if (ab->flags & AB8500_USB_FLAG_REGULATOR_SET_VOLTAGE) {
		volt = regulator_get_voltage(ab->v_ulpi);
		if ((volt != 1300000) && (volt != 1350000))
			dev_err(ab->dev, "Vintcore is not set to 1.3V volt=%d\n",
					volt);
	}

	ret = regulator_enable(ab->v_musb);
	if (ret)
		dev_err(ab->dev, "Failed to enable musb_1v8\n");
}