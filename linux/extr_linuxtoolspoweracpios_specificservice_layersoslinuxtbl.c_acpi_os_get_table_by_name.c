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
struct acpi_table_header {int dummy; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ AE_LIMIT ; 
 int /*<<< orphan*/  DYNAMIC_TABLE_DIR ; 
 int /*<<< orphan*/  STATIC_TABLE_DIR ; 
 int /*<<< orphan*/  gbl_dump_customized_tables ; 
 scalar_t__ gbl_dump_dynamic_tables ; 
 scalar_t__ osl_get_bios_table (char*,int /*<<< orphan*/ ,struct acpi_table_header**,int /*<<< orphan*/ *) ; 
 scalar_t__ osl_get_customized_table (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct acpi_table_header**,int /*<<< orphan*/ *) ; 
 scalar_t__ osl_table_initialize () ; 

acpi_status
acpi_os_get_table_by_name(char *signature,
			  u32 instance,
			  struct acpi_table_header **table,
			  acpi_physical_address *address)
{
	acpi_status status;

	/* Get main ACPI tables from memory on first invocation of this function */

	status = osl_table_initialize();
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/* Not a main ACPI table, attempt to extract it from the RSDT/XSDT */

	if (!gbl_dump_customized_tables) {

		/* Attempt to get the table from the memory */

		status =
		    osl_get_bios_table(signature, instance, table, address);
	} else {
		/* Attempt to get the table from the static directory */

		status = osl_get_customized_table(STATIC_TABLE_DIR, signature,
						  instance, table, address);
	}

	if (ACPI_FAILURE(status) && status == AE_LIMIT) {
		if (gbl_dump_dynamic_tables) {

			/* Attempt to get a dynamic table */

			status =
			    osl_get_customized_table(DYNAMIC_TABLE_DIR,
						     signature, instance, table,
						     address);
		}
	}

	return (status);
}