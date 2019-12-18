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
struct acpi_table_header {char* signature; } ;
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,struct acpi_table_header*) ; 
 int ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DB_BYTE_DISPLAY ; 
 int /*<<< orphan*/  acpi_tb_print_table_header (int /*<<< orphan*/ ,struct acpi_table_header*) ; 
 int /*<<< orphan*/  acpi_ut_dump_buffer_to_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_get_table_length (struct acpi_table_header*) ; 
 int ap_write_to_binary_file (struct acpi_table_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ gbl_binary_mode ; 
 int /*<<< orphan*/  gbl_output_file ; 
 scalar_t__ gbl_summary_mode ; 
 int /*<<< orphan*/  u8 ; 

__attribute__((used)) static int
ap_dump_table_buffer(struct acpi_table_header *table,
		     u32 instance, acpi_physical_address address)
{
	u32 table_length;

	table_length = ap_get_table_length(table);

	/* Print only the header if requested */

	if (gbl_summary_mode) {
		acpi_tb_print_table_header(address, table);
		return (0);
	}

	/* Dump to binary file if requested */

	if (gbl_binary_mode) {
		return (ap_write_to_binary_file(table, instance));
	}

	/*
	 * Dump the table with header for use with acpixtract utility.
	 * Note: simplest to just always emit a 64-bit address. acpi_xtract
	 * utility can handle this.
	 */
	fprintf(gbl_output_file, "%4.4s @ 0x%8.8X%8.8X\n",
		table->signature, ACPI_FORMAT_UINT64(address));

	acpi_ut_dump_buffer_to_file(gbl_output_file,
				    ACPI_CAST_PTR(u8, table), table_length,
				    DB_BYTE_DISPLAY, 0);
	fprintf(gbl_output_file, "\n");
	return (0);
}