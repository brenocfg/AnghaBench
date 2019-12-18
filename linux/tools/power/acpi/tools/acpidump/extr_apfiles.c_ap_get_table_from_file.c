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
struct acpi_table_header {int dummy; } ;
typedef  int acpi_size ;
typedef  int /*<<< orphan*/  ACPI_FILE ;

/* Variables and functions */
 struct acpi_table_header* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_table_header*) ; 
 int ACPI_UINT32_MAX ; 
 int cm_get_file_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fread (struct acpi_table_header*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

struct acpi_table_header *ap_get_table_from_file(char *pathname,
						 u32 *out_file_size)
{
	struct acpi_table_header *buffer = NULL;
	ACPI_FILE file;
	u32 file_size;
	acpi_size actual;

	/* Must use binary mode */

	file = fopen(pathname, "rb");
	if (!file) {
		fprintf(stderr, "Could not open input file: %s\n", pathname);
		return (NULL);
	}

	/* Need file size to allocate a buffer */

	file_size = cm_get_file_size(file);
	if (file_size == ACPI_UINT32_MAX) {
		fprintf(stderr,
			"Could not get input file size: %s\n", pathname);
		goto cleanup;
	}

	/* Allocate a buffer for the entire file */

	buffer = ACPI_ALLOCATE_ZEROED(file_size);
	if (!buffer) {
		fprintf(stderr,
			"Could not allocate file buffer of size: %u\n",
			file_size);
		goto cleanup;
	}

	/* Read the entire file */

	actual = fread(buffer, 1, file_size, file);
	if (actual != file_size) {
		fprintf(stderr, "Could not read input file: %s\n", pathname);
		ACPI_FREE(buffer);
		buffer = NULL;
		goto cleanup;
	}

	*out_file_size = file_size;

cleanup:
	fclose(file);
	return (buffer);
}