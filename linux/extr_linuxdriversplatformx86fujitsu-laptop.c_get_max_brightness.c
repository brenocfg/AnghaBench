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
struct fujitsu_bl {unsigned long long max_brightness; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 struct fujitsu_bl* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_max_brightness(struct acpi_device *device)
{
	struct fujitsu_bl *priv = acpi_driver_data(device);
	unsigned long long state = 0;
	acpi_status status = AE_OK;

	acpi_handle_debug(device->handle, "get max lcd level via RBLL\n");

	status = acpi_evaluate_integer(device->handle, "RBLL", NULL, &state);
	if (ACPI_FAILURE(status))
		return -1;

	priv->max_brightness = state;

	return priv->max_brightness;
}