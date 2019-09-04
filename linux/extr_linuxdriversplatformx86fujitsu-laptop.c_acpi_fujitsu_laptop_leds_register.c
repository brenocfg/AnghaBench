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
struct led_classdev {char* name; char* default_trigger; int /*<<< orphan*/  brightness_get; int /*<<< orphan*/  brightness_set_blocking; } ;
struct fujitsu_laptop {int flags_supported; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ECO_LED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FUNC_BUTTONS ; 
 int /*<<< orphan*/  FUNC_LEDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KEYBOARD_LAMPS ; 
 int LOGOLAMP_POWERON ; 
 int UNSUPPORTED_CMD ; 
 struct fujitsu_laptop* acpi_driver_data (struct acpi_device*) ; 
 int call_fext_func (struct acpi_device*,int /*<<< orphan*/ ,int,int,int) ; 
 struct led_classdev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ *,struct led_classdev*) ; 
 int /*<<< orphan*/  eco_led_get ; 
 int /*<<< orphan*/  eco_led_set ; 
 int /*<<< orphan*/  kblamps_get ; 
 int /*<<< orphan*/  kblamps_set ; 
 int /*<<< orphan*/  logolamp_get ; 
 int /*<<< orphan*/  logolamp_set ; 
 int /*<<< orphan*/  radio_led_get ; 
 int /*<<< orphan*/  radio_led_set ; 

__attribute__((used)) static int acpi_fujitsu_laptop_leds_register(struct acpi_device *device)
{
	struct fujitsu_laptop *priv = acpi_driver_data(device);
	struct led_classdev *led;
	int ret;

	if (call_fext_func(device,
			   FUNC_LEDS, 0x0, 0x0, 0x0) & LOGOLAMP_POWERON) {
		led = devm_kzalloc(&device->dev, sizeof(*led), GFP_KERNEL);
		if (!led)
			return -ENOMEM;

		led->name = "fujitsu::logolamp";
		led->brightness_set_blocking = logolamp_set;
		led->brightness_get = logolamp_get;
		ret = devm_led_classdev_register(&device->dev, led);
		if (ret)
			return ret;
	}

	if ((call_fext_func(device,
			    FUNC_LEDS, 0x0, 0x0, 0x0) & KEYBOARD_LAMPS) &&
	    (call_fext_func(device, FUNC_BUTTONS, 0x0, 0x0, 0x0) == 0x0)) {
		led = devm_kzalloc(&device->dev, sizeof(*led), GFP_KERNEL);
		if (!led)
			return -ENOMEM;

		led->name = "fujitsu::kblamps";
		led->brightness_set_blocking = kblamps_set;
		led->brightness_get = kblamps_get;
		ret = devm_led_classdev_register(&device->dev, led);
		if (ret)
			return ret;
	}

	/*
	 * Some Fujitsu laptops have a radio toggle button in place of a slide
	 * switch and all such machines appear to also have an RF LED.  Based on
	 * comparing DSDT tables of four Fujitsu Lifebook models (E744, E751,
	 * S7110, S8420; the first one has a radio toggle button, the other
	 * three have slide switches), bit 17 of flags_supported (the value
	 * returned by method S000 of ACPI device FUJ02E3) seems to indicate
	 * whether given model has a radio toggle button.
	 */
	if (priv->flags_supported & BIT(17)) {
		led = devm_kzalloc(&device->dev, sizeof(*led), GFP_KERNEL);
		if (!led)
			return -ENOMEM;

		led->name = "fujitsu::radio_led";
		led->brightness_set_blocking = radio_led_set;
		led->brightness_get = radio_led_get;
		led->default_trigger = "rfkill-any";
		ret = devm_led_classdev_register(&device->dev, led);
		if (ret)
			return ret;
	}

	/* Support for eco led is not always signaled in bit corresponding
	 * to the bit used to control the led. According to the DSDT table,
	 * bit 14 seems to indicate presence of said led as well.
	 * Confirm by testing the status.
	 */
	if ((call_fext_func(device, FUNC_LEDS, 0x0, 0x0, 0x0) & BIT(14)) &&
	    (call_fext_func(device,
			    FUNC_LEDS, 0x2, ECO_LED, 0x0) != UNSUPPORTED_CMD)) {
		led = devm_kzalloc(&device->dev, sizeof(*led), GFP_KERNEL);
		if (!led)
			return -ENOMEM;

		led->name = "fujitsu::eco_led";
		led->brightness_set_blocking = eco_led_set;
		led->brightness_get = eco_led_get;
		ret = devm_led_classdev_register(&device->dev, led);
		if (ret)
			return ret;
	}

	return 0;
}