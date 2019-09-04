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
struct asus_laptop {struct asus_laptop* name; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct asus_laptop* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  asus_backlight_exit (struct asus_laptop*) ; 
 int /*<<< orphan*/  asus_input_exit (struct asus_laptop*) ; 
 int /*<<< orphan*/  asus_led_exit (struct asus_laptop*) ; 
 int /*<<< orphan*/  asus_platform_exit (struct asus_laptop*) ; 
 int /*<<< orphan*/  asus_rfkill_exit (struct asus_laptop*) ; 
 int /*<<< orphan*/  kfree (struct asus_laptop*) ; 
 int /*<<< orphan*/  pega_accel_exit (struct asus_laptop*) ; 

__attribute__((used)) static int asus_acpi_remove(struct acpi_device *device)
{
	struct asus_laptop *asus = acpi_driver_data(device);

	asus_backlight_exit(asus);
	asus_rfkill_exit(asus);
	asus_led_exit(asus);
	asus_input_exit(asus);
	pega_accel_exit(asus);
	asus_platform_exit(asus);

	kfree(asus->name);
	kfree(asus);
	return 0;
}