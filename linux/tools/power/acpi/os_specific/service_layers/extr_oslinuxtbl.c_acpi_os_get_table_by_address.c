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
typedef  scalar_t__ u32 ;
struct acpi_table_header {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_HEADER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ ap_get_table_length (struct acpi_table_header*) ; 
 struct acpi_table_header* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct acpi_table_header*,struct acpi_table_header*,scalar_t__) ; 
 int /*<<< orphan*/  osl_map_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_table_header**) ; 
 int /*<<< orphan*/  osl_table_initialize () ; 
 int /*<<< orphan*/  osl_unmap_table (struct acpi_table_header*) ; 

acpi_status
acpi_os_get_table_by_address(acpi_physical_address address,
			     struct acpi_table_header **table)
{
	u32 table_length;
	struct acpi_table_header *mapped_table;
	struct acpi_table_header *local_table = NULL;
	acpi_status status = AE_OK;

	/* Get main ACPI tables from memory on first invocation of this function */

	status = osl_table_initialize();
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/* Map the table and validate it */

	status = osl_map_table(address, NULL, &mapped_table);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/* Copy table to local buffer and return it */

	table_length = ap_get_table_length(mapped_table);
	if (table_length == 0) {
		status = AE_BAD_HEADER;
		goto exit;
	}

	local_table = calloc(1, table_length);
	if (!local_table) {
		status = AE_NO_MEMORY;
		goto exit;
	}

	memcpy(local_table, mapped_table, table_length);

exit:
	osl_unmap_table(mapped_table);
	*table = local_table;
	return (status);
}