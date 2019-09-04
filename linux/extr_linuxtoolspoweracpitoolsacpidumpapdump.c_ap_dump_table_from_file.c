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
struct acpi_table_header {char* signature; int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (struct acpi_table_header*) ; 
 int /*<<< orphan*/  acpi_ut_valid_nameseg (char*) ; 
 int ap_dump_table_buffer (struct acpi_table_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct acpi_table_header* ap_get_table_from_file (char*,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ gbl_verbose_mode ; 
 int /*<<< orphan*/  stderr ; 

int ap_dump_table_from_file(char *pathname)
{
	struct acpi_table_header *table;
	u32 file_size = 0;
	int table_status = -1;

	/* Get the entire ACPI table from the file */

	table = ap_get_table_from_file(pathname, &file_size);
	if (!table) {
		return (-1);
	}

	if (!acpi_ut_valid_nameseg(table->signature)) {
		fprintf(stderr,
			"No valid ACPI signature was found in input file %s\n",
			pathname);
	}

	/* File must be at least as long as the table length */

	if (table->length > file_size) {
		fprintf(stderr,
			"Table length (0x%X) is too large for input file (0x%X) %s\n",
			table->length, file_size, pathname);
		goto exit;
	}

	if (gbl_verbose_mode) {
		fprintf(stderr,
			"Input file:  %s contains table [%4.4s], 0x%X (%u) bytes\n",
			pathname, table->signature, file_size, file_size);
	}

	table_status = ap_dump_table_buffer(table, 0, 0);

exit:
	ACPI_FREE(table);
	return (table_status);
}