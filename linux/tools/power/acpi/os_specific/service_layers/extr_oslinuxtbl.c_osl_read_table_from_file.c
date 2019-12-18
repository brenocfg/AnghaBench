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
typedef  int s32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPARE_NAMESEG (char*,char*) ; 
 scalar_t__ ACPI_VALIDATE_RSDP_SIG (char*) ; 
 int /*<<< orphan*/  AE_BAD_HEADER ; 
 int /*<<< orphan*/  AE_BAD_SIGNATURE ; 
 int /*<<< orphan*/  AE_INVALID_TABLE_LENGTH ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int ap_get_table_length (struct acpi_table_header*) ; 
 int /*<<< orphan*/  ap_is_valid_checksum (struct acpi_table_header*) ; 
 struct acpi_table_header* calloc (int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int fread (struct acpi_table_header*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osl_get_last_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static acpi_status
osl_read_table_from_file(char *filename,
			 acpi_size file_offset,
			 char *signature, struct acpi_table_header **table)
{
	FILE *table_file;
	struct acpi_table_header header;
	struct acpi_table_header *local_table = NULL;
	u32 table_length;
	s32 count;
	acpi_status status = AE_OK;

	/* Open the file */

	table_file = fopen(filename, "rb");
	if (table_file == NULL) {
		fprintf(stderr, "Could not open table file: %s\n", filename);
		return (osl_get_last_status(AE_NOT_FOUND));
	}

	fseek(table_file, file_offset, SEEK_SET);

	/* Read the Table header to get the table length */

	count = fread(&header, 1, sizeof(struct acpi_table_header), table_file);
	if (count != sizeof(struct acpi_table_header)) {
		fprintf(stderr, "Could not read table header: %s\n", filename);
		status = AE_BAD_HEADER;
		goto exit;
	}

	/* If signature is specified, it must match the table */

	if (signature) {
		if (ACPI_VALIDATE_RSDP_SIG(signature)) {
			if (!ACPI_VALIDATE_RSDP_SIG(header.signature)) {
				fprintf(stderr,
					"Incorrect RSDP signature: found %8.8s\n",
					header.signature);
				status = AE_BAD_SIGNATURE;
				goto exit;
			}
		} else if (!ACPI_COMPARE_NAMESEG(signature, header.signature)) {
			fprintf(stderr,
				"Incorrect signature: Expecting %4.4s, found %4.4s\n",
				signature, header.signature);
			status = AE_BAD_SIGNATURE;
			goto exit;
		}
	}

	table_length = ap_get_table_length(&header);
	if (table_length == 0) {
		status = AE_BAD_HEADER;
		goto exit;
	}

	/* Read the entire table into a local buffer */

	local_table = calloc(1, table_length);
	if (!local_table) {
		fprintf(stderr,
			"%4.4s: Could not allocate buffer for table of length %X\n",
			header.signature, table_length);
		status = AE_NO_MEMORY;
		goto exit;
	}

	fseek(table_file, file_offset, SEEK_SET);

	count = fread(local_table, 1, table_length, table_file);
	if (count != table_length) {
		fprintf(stderr, "%4.4s: Could not read table content\n",
			header.signature);
		status = AE_INVALID_TABLE_LENGTH;
		goto exit;
	}

	/* Validate checksum */

	(void)ap_is_valid_checksum(local_table);

exit:
	fclose(table_file);
	*table = local_table;
	return (status);
}