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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COPY_NAMESEG (char*,char*) ; 
 size_t ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  AE_BAD_SIGNATURE ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ isdigit (int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,scalar_t__*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static acpi_status
osl_table_name_from_file(char *filename, char *signature, u32 *instance)
{

	/* Ignore meaningless files */

	if (strlen(filename) < ACPI_NAMESEG_SIZE) {
		return (AE_BAD_SIGNATURE);
	}

	/* Extract instance number */

	if (isdigit((int)filename[ACPI_NAMESEG_SIZE])) {
		sscanf(&filename[ACPI_NAMESEG_SIZE], "%u", instance);
	} else if (strlen(filename) != ACPI_NAMESEG_SIZE) {
		return (AE_BAD_SIGNATURE);
	} else {
		*instance = 0;
	}

	/* Extract signature */

	ACPI_COPY_NAMESEG(signature, filename);
	return (AE_OK);
}