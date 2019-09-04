#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct acpi_table_header {int /*<<< orphan*/  signature; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_physical_address ;
struct TYPE_5__ {int length; } ;
struct TYPE_6__ {TYPE_1__ header; } ;

/* Variables and functions */
 scalar_t__* ACPI_CAST32 (int*) ; 
 scalar_t__* ACPI_CAST64 (int*) ; 
 int* ACPI_CAST8 (TYPE_2__*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_2__* gbl_rsdt ; 
 TYPE_2__* gbl_xsdt ; 
 int /*<<< orphan*/  osl_add_table_to_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ osl_can_use_xsdt () ; 
 int /*<<< orphan*/  osl_map_table (scalar_t__,int /*<<< orphan*/ *,struct acpi_table_header**) ; 
 int /*<<< orphan*/  osl_unmap_table (struct acpi_table_header*) ; 

__attribute__((used)) static acpi_status osl_list_bios_tables(void)
{
	struct acpi_table_header *mapped_table = NULL;
	u8 *table_data;
	u8 number_of_tables;
	u8 item_size;
	acpi_physical_address table_address = 0;
	acpi_status status = AE_OK;
	u32 i;

	if (osl_can_use_xsdt()) {
		item_size = sizeof(u64);
		table_data =
		    ACPI_CAST8(gbl_xsdt) + sizeof(struct acpi_table_header);
		number_of_tables =
		    (u8)((gbl_xsdt->header.length -
			  sizeof(struct acpi_table_header))
			 / item_size);
	} else {		/* Use RSDT if XSDT is not available */

		item_size = sizeof(u32);
		table_data =
		    ACPI_CAST8(gbl_rsdt) + sizeof(struct acpi_table_header);
		number_of_tables =
		    (u8)((gbl_rsdt->header.length -
			  sizeof(struct acpi_table_header))
			 / item_size);
	}

	/* Search RSDT/XSDT for the requested table */

	for (i = 0; i < number_of_tables; ++i, table_data += item_size) {
		if (osl_can_use_xsdt()) {
			table_address =
			    (acpi_physical_address)(*ACPI_CAST64(table_data));
		} else {
			table_address =
			    (acpi_physical_address)(*ACPI_CAST32(table_data));
		}

		/* Skip NULL entries in RSDT/XSDT */

		if (table_address == 0) {
			continue;
		}

		status = osl_map_table(table_address, NULL, &mapped_table);
		if (ACPI_FAILURE(status)) {
			return (status);
		}

		osl_add_table_to_list(mapped_table->signature, 0);
		osl_unmap_table(mapped_table);
	}

	return (AE_OK);
}