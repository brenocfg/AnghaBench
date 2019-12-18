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
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiGetData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_bus_private_data_handler ; 

int acpi_bus_get_private_data(ACPI_HANDLE handle, void **data)
{
	ACPI_STATUS status = AE_OK;

	if (!*data)
		return -1;

	status = AcpiGetData(handle, acpi_bus_private_data_handler, data);
	if (ACPI_FAILURE(status) || !*data) {
		DPRINT("No context for object [%p]\n", handle);
		return -1;
	}

	return 0;
}