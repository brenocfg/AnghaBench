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
struct backlight_device {int dummy; } ;
struct asus_laptop {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  METHOD_BRIGHTNESS_SET ; 
 struct asus_laptop* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ write_acpi_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int asus_set_brightness(struct backlight_device *bd, int value)
{
	struct asus_laptop *asus = bl_get_data(bd);

	if (write_acpi_int(asus->handle, METHOD_BRIGHTNESS_SET, value)) {
		pr_warn("Error changing brightness\n");
		return -EIO;
	}
	return 0;
}