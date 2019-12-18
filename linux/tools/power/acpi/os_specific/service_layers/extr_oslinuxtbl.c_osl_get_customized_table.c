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
typedef  scalar_t__ u32 ;
struct acpi_table_header {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_physical_address ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPARE_NAMESEG (char*,char*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  AE_LIMIT ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  REQUEST_FILE_ONLY ; 
 int /*<<< orphan*/  acpi_os_close_directory (void*) ; 
 char* acpi_os_get_next_filename (void*) ; 
 void* acpi_os_open_directory (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osl_get_last_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osl_read_table_from_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_table_header**) ; 
 int /*<<< orphan*/  osl_table_name_from_file (char*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,...) ; 

__attribute__((used)) static acpi_status
osl_get_customized_table(char *pathname,
			 char *signature,
			 u32 instance,
			 struct acpi_table_header **table,
			 acpi_physical_address *address)
{
	void *table_dir;
	u32 current_instance = 0;
	char temp_name[ACPI_NAMESEG_SIZE];
	char table_filename[PATH_MAX];
	char *filename;
	acpi_status status;

	/* Open the directory for customized tables */

	table_dir = acpi_os_open_directory(pathname, "*", REQUEST_FILE_ONLY);
	if (!table_dir) {
		return (osl_get_last_status(AE_NOT_FOUND));
	}

	/* Attempt to find the table in the directory */

	while ((filename = acpi_os_get_next_filename(table_dir))) {

		/* Ignore meaningless files */

		if (!ACPI_COMPARE_NAMESEG(filename, signature)) {
			continue;
		}

		/* Extract table name and instance number */

		status =
		    osl_table_name_from_file(filename, temp_name,
					     &current_instance);

		/* Ignore meaningless files */

		if (ACPI_FAILURE(status) || current_instance != instance) {
			continue;
		}

		/* Create the table pathname */

		if (instance != 0) {
			sprintf(table_filename, "%s/%4.4s%d", pathname,
				temp_name, instance);
		} else {
			sprintf(table_filename, "%s/%4.4s", pathname,
				temp_name);
		}
		break;
	}

	acpi_os_close_directory(table_dir);

	if (!filename) {
		return (AE_LIMIT);
	}

	/* There is no physical address saved for customized tables, use zero */

	*address = 0;
	status = osl_read_table_from_file(table_filename, 0, NULL, table);

	return (status);
}