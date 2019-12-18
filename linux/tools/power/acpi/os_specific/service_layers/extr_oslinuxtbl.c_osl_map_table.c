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
typedef  int u32 ;
struct acpi_table_header {char* signature; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPARE_NAMESEG (char*,char*) ; 
 int ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_VALIDATE_RSDP_SIG (char*) ; 
 int /*<<< orphan*/  AE_BAD_ADDRESS ; 
 int /*<<< orphan*/  AE_BAD_HEADER ; 
 int /*<<< orphan*/  AE_BAD_SIGNATURE ; 
 int /*<<< orphan*/  AE_INVALID_TABLE_LENGTH ; 
 int /*<<< orphan*/  AE_OK ; 
 struct acpi_table_header* acpi_os_map_memory (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_os_unmap_memory (struct acpi_table_header*,int) ; 
 int ap_get_table_length (struct acpi_table_header*) ; 
 int /*<<< orphan*/  ap_is_valid_checksum (struct acpi_table_header*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  osl_get_last_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static acpi_status
osl_map_table(acpi_size address,
	      char *signature, struct acpi_table_header **table)
{
	struct acpi_table_header *mapped_table;
	u32 length;

	if (!address) {
		return (AE_BAD_ADDRESS);
	}

	/*
	 * Map the header so we can get the table length.
	 * Use sizeof (struct acpi_table_header) as:
	 * 1. it is bigger than 24 to include RSDP->Length
	 * 2. it is smaller than sizeof (struct acpi_table_rsdp)
	 */
	mapped_table =
	    acpi_os_map_memory(address, sizeof(struct acpi_table_header));
	if (!mapped_table) {
		fprintf(stderr, "Could not map table header at 0x%8.8X%8.8X\n",
			ACPI_FORMAT_UINT64(address));
		return (osl_get_last_status(AE_BAD_ADDRESS));
	}

	/* If specified, signature must match */

	if (signature) {
		if (ACPI_VALIDATE_RSDP_SIG(signature)) {
			if (!ACPI_VALIDATE_RSDP_SIG(mapped_table->signature)) {
				acpi_os_unmap_memory(mapped_table,
						     sizeof(struct
							    acpi_table_header));
				return (AE_BAD_SIGNATURE);
			}
		} else
		    if (!ACPI_COMPARE_NAMESEG
			(signature, mapped_table->signature)) {
			acpi_os_unmap_memory(mapped_table,
					     sizeof(struct acpi_table_header));
			return (AE_BAD_SIGNATURE);
		}
	}

	/* Map the entire table */

	length = ap_get_table_length(mapped_table);
	acpi_os_unmap_memory(mapped_table, sizeof(struct acpi_table_header));
	if (length == 0) {
		return (AE_BAD_HEADER);
	}

	mapped_table = acpi_os_map_memory(address, length);
	if (!mapped_table) {
		fprintf(stderr,
			"Could not map table at 0x%8.8X%8.8X length %8.8X\n",
			ACPI_FORMAT_UINT64(address), length);
		return (osl_get_last_status(AE_INVALID_TABLE_LENGTH));
	}

	(void)ap_is_valid_checksum(mapped_table);

	*table = mapped_table;
	return (AE_OK);
}