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
struct thermal_zone_device {int /*<<< orphan*/  device; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ AE_ERROR ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  GET_AUX0 ; 
 int /*<<< orphan*/  GET_AUX1 ; 
 int /*<<< orphan*/  SET_AUX0 ; 
 int /*<<< orphan*/  SET_AUX1 ; 
 int acpi_bus_get_private_data (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ acpi_get_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aux0_show ; 
 int /*<<< orphan*/ * aux0_store ; 
 int /*<<< orphan*/  aux1_show ; 
 int /*<<< orphan*/ * aux1_store ; 
 int /*<<< orphan*/  bios_enabled_show ; 
 int intel_menlow_add_one_attribute (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_menlow_unregister_sensor () ; 

__attribute__((used)) static acpi_status intel_menlow_register_sensor(acpi_handle handle, u32 lvl,
						void *context, void **rv)
{
	acpi_status status;
	acpi_handle dummy;
	struct thermal_zone_device *thermal;
	int result;

	result = acpi_bus_get_private_data(handle, (void **)&thermal);
	if (result)
		return 0;

	/* _TZ must have the AUX0/1 methods */
	status = acpi_get_handle(handle, GET_AUX0, &dummy);
	if (ACPI_FAILURE(status))
		return (status == AE_NOT_FOUND) ? AE_OK : status;

	status = acpi_get_handle(handle, SET_AUX0, &dummy);
	if (ACPI_FAILURE(status))
		return (status == AE_NOT_FOUND) ? AE_OK : status;

	result = intel_menlow_add_one_attribute("aux0", 0644,
						aux0_show, aux0_store,
						&thermal->device, handle);
	if (result)
		return AE_ERROR;

	status = acpi_get_handle(handle, GET_AUX1, &dummy);
	if (ACPI_FAILURE(status))
		goto aux1_not_found;

	status = acpi_get_handle(handle, SET_AUX1, &dummy);
	if (ACPI_FAILURE(status))
		goto aux1_not_found;

	result = intel_menlow_add_one_attribute("aux1", 0644,
						aux1_show, aux1_store,
						&thermal->device, handle);
	if (result) {
		intel_menlow_unregister_sensor();
		return AE_ERROR;
	}

	/*
	 * create the "dabney_enabled" attribute which means the user app
	 * should be loaded or not
	 */

	result = intel_menlow_add_one_attribute("bios_enabled", 0444,
						bios_enabled_show, NULL,
						&thermal->device, handle);
	if (result) {
		intel_menlow_unregister_sensor();
		return AE_ERROR;
	}

	return AE_OK;

 aux1_not_found:
	if (status == AE_NOT_FOUND)
		return AE_OK;

	intel_menlow_unregister_sensor();
	return status;
}