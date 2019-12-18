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
typedef  scalar_t__ ACPI_FILE ;

/* Variables and functions */
 scalar_t__ ap_is_existing_file (char*) ; 
 scalar_t__ fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ gbl_output_file ; 
 char* gbl_output_filename ; 
 int /*<<< orphan*/  stderr ; 

int ap_open_output_file(char *pathname)
{
	ACPI_FILE file;

	/* If file exists, prompt for overwrite */

	if (ap_is_existing_file(pathname) != 0) {
		return (-1);
	}

	/* Point stdout to the file */

	file = fopen(pathname, "w");
	if (!file) {
		fprintf(stderr, "Could not open output file: %s\n", pathname);
		return (-1);
	}

	/* Save the file and path */

	gbl_output_file = file;
	gbl_output_filename = pathname;
	return (0);
}