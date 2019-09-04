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
struct osl_table_info {scalar_t__ instance; int /*<<< orphan*/  signature; struct osl_table_info* next; } ;
struct acpi_table_header {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_LIMIT ; 
 int /*<<< orphan*/  acpi_os_get_table_by_name (int /*<<< orphan*/ ,scalar_t__,struct acpi_table_header**,int /*<<< orphan*/ *) ; 
 scalar_t__ gbl_table_count ; 
 struct osl_table_info* gbl_table_list_head ; 
 int /*<<< orphan*/  osl_table_initialize () ; 

acpi_status
acpi_os_get_table_by_index(u32 index,
			   struct acpi_table_header **table,
			   u32 *instance, acpi_physical_address *address)
{
	struct osl_table_info *info;
	acpi_status status;
	u32 i;

	/* Get main ACPI tables from memory on first invocation of this function */

	status = osl_table_initialize();
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/* Validate Index */

	if (index >= gbl_table_count) {
		return (AE_LIMIT);
	}

	/* Point to the table list entry specified by the Index argument */

	info = gbl_table_list_head;
	for (i = 0; i < index; i++) {
		info = info->next;
	}

	/* Now we can just get the table via the signature */

	status = acpi_os_get_table_by_name(info->signature, info->instance,
					   table, address);

	if (ACPI_SUCCESS(status)) {
		*instance = info->instance;
	}
	return (status);
}