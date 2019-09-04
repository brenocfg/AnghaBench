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
struct acpi_table_header {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_ACPI_TABLES ; 

acpi_status
acpi_os_table_override(struct acpi_table_header *existing_table,
		       struct acpi_table_header **new_table)
{

	if (!existing_table || !new_table) {
		return (AE_BAD_PARAMETER);
	}

	*new_table = NULL;

#ifdef ACPI_EXEC_APP

	ae_table_override(existing_table, new_table);
	return (AE_OK);
#else

	return (AE_NO_ACPI_TABLES);
#endif
}