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
struct fujitsu_bl {int max_brightness; int brightness_level; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 struct fujitsu_bl* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_execute_simple_method (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  acpi_handle_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  acpi_has_method (int /*<<< orphan*/ ,char*) ; 
 int use_alt_lcd_levels ; 

__attribute__((used)) static int set_lcd_level(struct acpi_device *device, int level)
{
	struct fujitsu_bl *priv = acpi_driver_data(device);
	acpi_status status;
	char *method;

	switch (use_alt_lcd_levels) {
	case -1:
		if (acpi_has_method(device->handle, "SBL2"))
			method = "SBL2";
		else
			method = "SBLL";
		break;
	case 1:
		method = "SBL2";
		break;
	default:
		method = "SBLL";
		break;
	}

	acpi_handle_debug(device->handle, "set lcd level via %s [%d]\n", method,
			  level);

	if (level < 0 || level >= priv->max_brightness)
		return -EINVAL;

	status = acpi_execute_simple_method(device->handle, method, level);
	if (ACPI_FAILURE(status)) {
		acpi_handle_err(device->handle, "Failed to evaluate %s\n",
				method);
		return -ENODEV;
	}

	priv->brightness_level = level;

	return 0;
}