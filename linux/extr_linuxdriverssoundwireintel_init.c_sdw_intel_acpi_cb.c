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
typedef  int /*<<< orphan*/  u32 ;
struct sdw_intel_res {int /*<<< orphan*/  handle; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static acpi_status sdw_intel_acpi_cb(acpi_handle handle, u32 level,
					void *cdata, void **return_value)
{
	struct sdw_intel_res *res = cdata;
	struct acpi_device *adev;

	if (acpi_bus_get_device(handle, &adev)) {
		dev_err(&adev->dev, "Couldn't find ACPI handle\n");
		return AE_NOT_FOUND;
	}

	res->handle = handle;
	return AE_OK;
}