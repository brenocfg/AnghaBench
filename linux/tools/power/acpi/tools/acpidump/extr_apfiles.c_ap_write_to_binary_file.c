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
typedef  int /*<<< orphan*/  instance_str ;
typedef  int acpi_size ;
typedef  int /*<<< orphan*/  ACPI_FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COPY_NAMESEG (char*,char*) ; 
 int ACPI_NAMESEG_SIZE ; 
 char* ACPI_RSDP_NAME ; 
 scalar_t__ ACPI_VALIDATE_RSDP_SIG (char*) ; 
 char* FILE_SUFFIX_BINARY_TABLE ; 
 int ap_get_table_length (struct acpi_table_header*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int fwrite (struct acpi_table_header*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gbl_verbose_mode ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ tolower (int) ; 

int ap_write_to_binary_file(struct acpi_table_header *table, u32 instance)
{
	char filename[ACPI_NAMESEG_SIZE + 16];
	char instance_str[16];
	ACPI_FILE file;
	acpi_size actual;
	u32 table_length;

	/* Obtain table length */

	table_length = ap_get_table_length(table);

	/* Construct lower-case filename from the table local signature */

	if (ACPI_VALIDATE_RSDP_SIG(table->signature)) {
		ACPI_COPY_NAMESEG(filename, ACPI_RSDP_NAME);
	} else {
		ACPI_COPY_NAMESEG(filename, table->signature);
	}

	filename[0] = (char)tolower((int)filename[0]);
	filename[1] = (char)tolower((int)filename[1]);
	filename[2] = (char)tolower((int)filename[2]);
	filename[3] = (char)tolower((int)filename[3]);
	filename[ACPI_NAMESEG_SIZE] = 0;

	/* Handle multiple SSDts - create different filenames for each */

	if (instance > 0) {
		snprintf(instance_str, sizeof(instance_str), "%u", instance);
		strcat(filename, instance_str);
	}

	strcat(filename, FILE_SUFFIX_BINARY_TABLE);

	if (gbl_verbose_mode) {
		fprintf(stderr,
			"Writing [%4.4s] to binary file: %s 0x%X (%u) bytes\n",
			table->signature, filename, table->length,
			table->length);
	}

	/* Open the file and dump the entire table in binary mode */

	file = fopen(filename, "wb");
	if (!file) {
		fprintf(stderr, "Could not open output file: %s\n", filename);
		return (-1);
	}

	actual = fwrite(table, 1, table_length, file);
	if (actual != table_length) {
		fprintf(stderr, "Error writing binary output file: %s\n",
			filename);
		fclose(file);
		return (-1);
	}

	fclose(file);
	return (0);
}