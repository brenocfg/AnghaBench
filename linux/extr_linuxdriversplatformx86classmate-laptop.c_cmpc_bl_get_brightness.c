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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  cmpc_get_brightness (int /*<<< orphan*/ ,unsigned long long*) ; 

__attribute__((used)) static int cmpc_bl_get_brightness(struct backlight_device *bd)
{
	acpi_status status;
	acpi_handle handle;
	unsigned long long brightness;

	handle = bl_get_data(bd);
	status = cmpc_get_brightness(handle, &brightness);
	if (ACPI_SUCCESS(status))
		return brightness;
	else
		return -1;
}