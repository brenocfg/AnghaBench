#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct acpi_table_header {int length; char* signature; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_physical_address ;
struct TYPE_8__ {scalar_t__ length; } ;
struct TYPE_12__ {scalar_t__ dsdt; scalar_t__ facs; TYPE_1__ header; scalar_t__ Xfacs; scalar_t__ Xdsdt; } ;
struct TYPE_11__ {scalar_t__ rsdt_physical_address; scalar_t__ xsdt_physical_address; } ;
struct TYPE_9__ {int length; } ;
struct TYPE_10__ {TYPE_2__ header; } ;

/* Variables and functions */
 scalar_t__* ACPI_CAST32 (int*) ; 
 scalar_t__* ACPI_CAST64 (int*) ; 
 int* ACPI_CAST8 (TYPE_3__*) ; 
 scalar_t__ ACPI_COMPARE_NAMESEG (char*,char*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 char* ACPI_RSDP_NAME ; 
 char* ACPI_SIG_DSDT ; 
 char* ACPI_SIG_FACS ; 
 char* ACPI_SIG_RSDP ; 
 char* ACPI_SIG_RSDT ; 
 char* ACPI_SIG_XSDT ; 
 int /*<<< orphan*/  AE_BAD_HEADER ; 
 int /*<<< orphan*/  AE_BAD_SIGNATURE ; 
 int /*<<< orphan*/  AE_LIMIT ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ MIN_FADT_FOR_DSDT ; 
 scalar_t__ MIN_FADT_FOR_FACS ; 
 scalar_t__ MIN_FADT_FOR_XDSDT ; 
 scalar_t__ MIN_FADT_FOR_XFACS ; 
 int ap_get_table_length (struct acpi_table_header*) ; 
 struct acpi_table_header* calloc (int,int) ; 
 TYPE_6__* gbl_fadt ; 
 int /*<<< orphan*/  gbl_revision ; 
 TYPE_5__ gbl_rsdp ; 
 scalar_t__ gbl_rsdp_address ; 
 TYPE_3__* gbl_rsdt ; 
 TYPE_3__* gbl_xsdt ; 
 int /*<<< orphan*/  memcpy (struct acpi_table_header*,struct acpi_table_header*,int) ; 
 scalar_t__ osl_can_use_xsdt () ; 
 int /*<<< orphan*/  osl_map_table (scalar_t__,char*,struct acpi_table_header**) ; 
 int /*<<< orphan*/  osl_unmap_table (struct acpi_table_header*) ; 

__attribute__((used)) static acpi_status
osl_get_bios_table(char *signature,
		   u32 instance,
		   struct acpi_table_header **table,
		   acpi_physical_address *address)
{
	struct acpi_table_header *local_table = NULL;
	struct acpi_table_header *mapped_table = NULL;
	u8 *table_data;
	u8 number_of_tables;
	u8 item_size;
	u32 current_instance = 0;
	acpi_physical_address table_address;
	acpi_physical_address first_table_address = 0;
	u32 table_length = 0;
	acpi_status status = AE_OK;
	u32 i;

	/* Handle special tables whose addresses are not in RSDT/XSDT */

	if (ACPI_COMPARE_NAMESEG(signature, ACPI_RSDP_NAME) ||
	    ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_RSDT) ||
	    ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_XSDT) ||
	    ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_DSDT) ||
	    ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_FACS)) {

find_next_instance:

		table_address = 0;

		/*
		 * Get the appropriate address, either 32-bit or 64-bit. Be very
		 * careful about the FADT length and validate table addresses.
		 * Note: The 64-bit addresses have priority.
		 */
		if (ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_DSDT)) {
			if (current_instance < 2) {
				if ((gbl_fadt->header.length >=
				     MIN_FADT_FOR_XDSDT) && gbl_fadt->Xdsdt
				    && current_instance == 0) {
					table_address =
					    (acpi_physical_address)gbl_fadt->
					    Xdsdt;
				} else
				    if ((gbl_fadt->header.length >=
					 MIN_FADT_FOR_DSDT)
					&& gbl_fadt->dsdt !=
					first_table_address) {
					table_address =
					    (acpi_physical_address)gbl_fadt->
					    dsdt;
				}
			}
		} else if (ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_FACS)) {
			if (current_instance < 2) {
				if ((gbl_fadt->header.length >=
				     MIN_FADT_FOR_XFACS) && gbl_fadt->Xfacs
				    && current_instance == 0) {
					table_address =
					    (acpi_physical_address)gbl_fadt->
					    Xfacs;
				} else
				    if ((gbl_fadt->header.length >=
					 MIN_FADT_FOR_FACS)
					&& gbl_fadt->facs !=
					first_table_address) {
					table_address =
					    (acpi_physical_address)gbl_fadt->
					    facs;
				}
			}
		} else if (ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_XSDT)) {
			if (!gbl_revision) {
				return (AE_BAD_SIGNATURE);
			}
			if (current_instance == 0) {
				table_address =
				    (acpi_physical_address)gbl_rsdp.
				    xsdt_physical_address;
			}
		} else if (ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_RSDT)) {
			if (current_instance == 0) {
				table_address =
				    (acpi_physical_address)gbl_rsdp.
				    rsdt_physical_address;
			}
		} else {
			if (current_instance == 0) {
				table_address =
				    (acpi_physical_address)gbl_rsdp_address;
				signature = ACPI_SIG_RSDP;
			}
		}

		if (table_address == 0) {
			goto exit_find_table;
		}

		/* Now we can get the requested special table */

		status = osl_map_table(table_address, signature, &mapped_table);
		if (ACPI_FAILURE(status)) {
			return (status);
		}

		table_length = ap_get_table_length(mapped_table);
		if (first_table_address == 0) {
			first_table_address = table_address;
		}

		/* Match table instance */

		if (current_instance != instance) {
			osl_unmap_table(mapped_table);
			mapped_table = NULL;
			current_instance++;
			goto find_next_instance;
		}
	} else {		/* Case for a normal ACPI table */

		if (osl_can_use_xsdt()) {
			item_size = sizeof(u64);
			table_data =
			    ACPI_CAST8(gbl_xsdt) +
			    sizeof(struct acpi_table_header);
			number_of_tables =
			    (u8)((gbl_xsdt->header.length -
				  sizeof(struct acpi_table_header))
				 / item_size);
		} else {	/* Use RSDT if XSDT is not available */

			item_size = sizeof(u32);
			table_data =
			    ACPI_CAST8(gbl_rsdt) +
			    sizeof(struct acpi_table_header);
			number_of_tables =
			    (u8)((gbl_rsdt->header.length -
				  sizeof(struct acpi_table_header))
				 / item_size);
		}

		/* Search RSDT/XSDT for the requested table */

		for (i = 0; i < number_of_tables; ++i, table_data += item_size) {
			if (osl_can_use_xsdt()) {
				table_address =
				    (acpi_physical_address)(*ACPI_CAST64
							    (table_data));
			} else {
				table_address =
				    (acpi_physical_address)(*ACPI_CAST32
							    (table_data));
			}

			/* Skip NULL entries in RSDT/XSDT */

			if (table_address == 0) {
				continue;
			}

			status =
			    osl_map_table(table_address, NULL, &mapped_table);
			if (ACPI_FAILURE(status)) {
				return (status);
			}
			table_length = mapped_table->length;

			/* Does this table match the requested signature? */

			if (!ACPI_COMPARE_NAMESEG
			    (mapped_table->signature, signature)) {
				osl_unmap_table(mapped_table);
				mapped_table = NULL;
				continue;
			}

			/* Match table instance (for SSDT/UEFI tables) */

			if (current_instance != instance) {
				osl_unmap_table(mapped_table);
				mapped_table = NULL;
				current_instance++;
				continue;
			}

			break;
		}
	}

exit_find_table:

	if (!mapped_table) {
		return (AE_LIMIT);
	}

	if (table_length == 0) {
		status = AE_BAD_HEADER;
		goto exit;
	}

	/* Copy table to local buffer and return it */

	local_table = calloc(1, table_length);
	if (!local_table) {
		status = AE_NO_MEMORY;
		goto exit;
	}

	memcpy(local_table, mapped_table, table_length);
	*address = table_address;
	*table = local_table;

exit:
	osl_unmap_table(mapped_table);
	return (status);
}