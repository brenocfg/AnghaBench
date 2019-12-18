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
typedef  scalar_t__ u64 ;
struct acpi_table_header {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_physical_address ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_FORMAT_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_table_header*) ; 
 char* acpi_format_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_get_table_by_address (scalar_t__,struct acpi_table_header**) ; 
 int /*<<< orphan*/  acpi_ut_strtoul64 (char*,scalar_t__*) ; 
 int ap_dump_table_buffer (struct acpi_table_header*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int ap_dump_table_by_address(char *ascii_address)
{
	acpi_physical_address address;
	struct acpi_table_header *table;
	acpi_status status;
	int table_status;
	u64 long_address;

	/* Convert argument to an integer physical address */

	status = acpi_ut_strtoul64(ascii_address, &long_address);
	if (ACPI_FAILURE(status)) {
		fprintf(stderr, "%s: Could not convert to a physical address\n",
			ascii_address);
		return (-1);
	}

	address = (acpi_physical_address)long_address;
	status = acpi_os_get_table_by_address(address, &table);
	if (ACPI_FAILURE(status)) {
		fprintf(stderr, "Could not get table at 0x%8.8X%8.8X, %s\n",
			ACPI_FORMAT_UINT64(address),
			acpi_format_exception(status));
		return (-1);
	}

	table_status = ap_dump_table_buffer(table, 0, address);
	ACPI_FREE(table);
	return (table_status);
}