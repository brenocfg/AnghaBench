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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_OPTION_ERROR (char*,int /*<<< orphan*/ ) ; 
 char* acpi_gbl_optarg ; 
 size_t acpi_gbl_optind ; 
 int current_char_ptr ; 

int acpi_getopt_argument(int argc, char **argv)
{

	acpi_gbl_optind--;
	current_char_ptr++;

	if (argv[acpi_gbl_optind][(int)(current_char_ptr + 1)] != '\0') {
		acpi_gbl_optarg =
		    &argv[acpi_gbl_optind++][(int)(current_char_ptr + 1)];
	} else if (++acpi_gbl_optind >= argc) {
		ACPI_OPTION_ERROR("\nOption requires an argument", 0);

		current_char_ptr = 1;
		return (-1);
	} else {
		acpi_gbl_optarg = argv[acpi_gbl_optind++];
	}

	current_char_ptr = 1;
	return (0);
}