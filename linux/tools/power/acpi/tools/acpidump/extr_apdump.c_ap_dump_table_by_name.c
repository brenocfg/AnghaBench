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
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (char*,char*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_table_header*) ; 
 int ACPI_NAMESEG_SIZE ; 
 char* ACPI_SIG_FADT ; 
 char* ACPI_SIG_MADT ; 
 int /*<<< orphan*/  AE_LIMIT ; 
 scalar_t__ AP_MAX_ACPI_FILES ; 
 char* acpi_format_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_get_table_by_name (char*,scalar_t__,struct acpi_table_header**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_strupr (char*) ; 
 int ap_dump_table_buffer (struct acpi_table_header*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

int ap_dump_table_by_name(char *signature)
{
	char local_signature[ACPI_NAMESEG_SIZE + 1];
	u32 instance;
	struct acpi_table_header *table;
	acpi_physical_address address;
	acpi_status status;
	int table_status;

	if (strlen(signature) != ACPI_NAMESEG_SIZE) {
		fprintf(stderr,
			"Invalid table signature [%s]: must be exactly 4 characters\n",
			signature);
		return (-1);
	}

	/* Table signatures are expected to be uppercase */

	strcpy(local_signature, signature);
	acpi_ut_strupr(local_signature);

	/* To be friendly, handle tables whose signatures do not match the name */

	if (ACPI_COMPARE_NAMESEG(local_signature, "FADT")) {
		strcpy(local_signature, ACPI_SIG_FADT);
	} else if (ACPI_COMPARE_NAMESEG(local_signature, "MADT")) {
		strcpy(local_signature, ACPI_SIG_MADT);
	}

	/* Dump all instances of this signature (to handle multiple SSDTs) */

	for (instance = 0; instance < AP_MAX_ACPI_FILES; instance++) {
		status = acpi_os_get_table_by_name(local_signature, instance,
						   &table, &address);
		if (ACPI_FAILURE(status)) {

			/* AE_LIMIT means that no more tables are available */

			if (status == AE_LIMIT) {
				return (0);
			}

			fprintf(stderr,
				"Could not get ACPI table with signature [%s], %s\n",
				local_signature, acpi_format_exception(status));
			return (-1);
		}

		table_status = ap_dump_table_buffer(table, instance, address);
		ACPI_FREE(table);

		if (table_status) {
			break;
		}
	}

	/* Something seriously bad happened if the loop terminates here */

	return (-1);
}