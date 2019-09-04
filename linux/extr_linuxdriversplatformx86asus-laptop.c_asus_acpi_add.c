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
struct asus_laptop {int /*<<< orphan*/  is_pega_lucid; struct acpi_device* device; int /*<<< orphan*/  handle; } ;
struct acpi_device {struct asus_laptop* driver_data; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_LAPTOP_CLASS ; 
 int /*<<< orphan*/  ASUS_LAPTOP_DEVICE_NAME ; 
 int /*<<< orphan*/  ASUS_LAPTOP_VERSION ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ acpi_backlight_vendor ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 scalar_t__ acpi_video_get_backlight_type () ; 
 int asus_acpi_init (struct asus_laptop*) ; 
 int /*<<< orphan*/  asus_backlight_exit (struct asus_laptop*) ; 
 int asus_backlight_init (struct asus_laptop*) ; 
 int /*<<< orphan*/  asus_check_pega_lucid (struct asus_laptop*) ; 
 int asus_device_present ; 
 int /*<<< orphan*/  asus_dmi_check () ; 
 int /*<<< orphan*/  asus_input_exit (struct asus_laptop*) ; 
 int asus_input_init (struct asus_laptop*) ; 
 int /*<<< orphan*/  asus_led_exit (struct asus_laptop*) ; 
 int asus_led_init (struct asus_laptop*) ; 
 int /*<<< orphan*/  asus_platform_exit (struct asus_laptop*) ; 
 int asus_platform_init (struct asus_laptop*) ; 
 int /*<<< orphan*/  asus_rfkill_exit (struct asus_laptop*) ; 
 int asus_rfkill_init (struct asus_laptop*) ; 
 int /*<<< orphan*/  kfree (struct asus_laptop*) ; 
 struct asus_laptop* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pega_accel_exit (struct asus_laptop*) ; 
 int pega_accel_init (struct asus_laptop*) ; 
 int pega_rfkill_init (struct asus_laptop*) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asus_acpi_add(struct acpi_device *device)
{
	struct asus_laptop *asus;
	int result;

	pr_notice("Asus Laptop Support version %s\n",
		  ASUS_LAPTOP_VERSION);
	asus = kzalloc(sizeof(struct asus_laptop), GFP_KERNEL);
	if (!asus)
		return -ENOMEM;
	asus->handle = device->handle;
	strcpy(acpi_device_name(device), ASUS_LAPTOP_DEVICE_NAME);
	strcpy(acpi_device_class(device), ASUS_LAPTOP_CLASS);
	device->driver_data = asus;
	asus->device = device;

	asus_dmi_check();

	result = asus_acpi_init(asus);
	if (result)
		goto fail_platform;

	/*
	 * Need platform type detection first, then the platform
	 * device.  It is used as a parent for the sub-devices below.
	 */
	asus->is_pega_lucid = asus_check_pega_lucid(asus);
	result = asus_platform_init(asus);
	if (result)
		goto fail_platform;

	if (acpi_video_get_backlight_type() == acpi_backlight_vendor) {
		result = asus_backlight_init(asus);
		if (result)
			goto fail_backlight;
	}

	result = asus_input_init(asus);
	if (result)
		goto fail_input;

	result = asus_led_init(asus);
	if (result)
		goto fail_led;

	result = asus_rfkill_init(asus);
	if (result && result != -ENODEV)
		goto fail_rfkill;

	result = pega_accel_init(asus);
	if (result && result != -ENODEV)
		goto fail_pega_accel;

	result = pega_rfkill_init(asus);
	if (result && result != -ENODEV)
		goto fail_pega_rfkill;

	asus_device_present = true;
	return 0;

fail_pega_rfkill:
	pega_accel_exit(asus);
fail_pega_accel:
	asus_rfkill_exit(asus);
fail_rfkill:
	asus_led_exit(asus);
fail_led:
	asus_input_exit(asus);
fail_input:
	asus_backlight_exit(asus);
fail_backlight:
	asus_platform_exit(asus);
fail_platform:
	kfree(asus);

	return result;
}