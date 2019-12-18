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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  REQUEST_FILE_ONLY ; 
 int /*<<< orphan*/  acpi_os_close_directory (void*) ; 
 char* acpi_os_get_next_filename (void*) ; 
 void* acpi_os_open_directory (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osl_add_table_to_list (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osl_get_last_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osl_table_name_from_file (char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static acpi_status osl_list_customized_tables(char *directory)
{
	void *table_dir;
	u32 instance;
	char temp_name[ACPI_NAMESEG_SIZE];
	char *filename;
	acpi_status status = AE_OK;

	/* Open the requested directory */

	table_dir = acpi_os_open_directory(directory, "*", REQUEST_FILE_ONLY);
	if (!table_dir) {
		return (osl_get_last_status(AE_NOT_FOUND));
	}

	/* Examine all entries in this directory */

	while ((filename = acpi_os_get_next_filename(table_dir))) {

		/* Extract table name and instance number */

		status =
		    osl_table_name_from_file(filename, temp_name, &instance);

		/* Ignore meaningless files */

		if (ACPI_FAILURE(status)) {
			continue;
		}

		/* Add new info node to global table list */

		status = osl_add_table_to_list(temp_name, instance);
		if (ACPI_FAILURE(status)) {
			break;
		}
	}

	acpi_os_close_directory(table_dir);
	return (status);
}