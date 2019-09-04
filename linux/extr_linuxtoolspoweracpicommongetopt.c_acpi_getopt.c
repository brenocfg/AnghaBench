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
 int /*<<< orphan*/  ACPI_OPTION_ERROR (char*,int) ; 
 int ACPI_OPT_END ; 
 char* acpi_gbl_optarg ; 
 int acpi_gbl_optind ; 
 char acpi_gbl_sub_opt_char ; 
 int current_char_ptr ; 
 char* strchr (char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

int acpi_getopt(int argc, char **argv, char *opts)
{
	int current_char;
	char *opts_ptr;

	if (current_char_ptr == 1) {
		if (acpi_gbl_optind >= argc ||
		    argv[acpi_gbl_optind][0] != '-' ||
		    argv[acpi_gbl_optind][1] == '\0') {
			return (ACPI_OPT_END);
		} else if (strcmp(argv[acpi_gbl_optind], "--") == 0) {
			acpi_gbl_optind++;
			return (ACPI_OPT_END);
		}
	}

	/* Get the option */

	current_char = argv[acpi_gbl_optind][current_char_ptr];

	/* Make sure that the option is legal */

	if (current_char == ':' ||
	    (opts_ptr = strchr(opts, current_char)) == NULL) {
		ACPI_OPTION_ERROR("Illegal option: -", current_char);

		if (argv[acpi_gbl_optind][++current_char_ptr] == '\0') {
			acpi_gbl_optind++;
			current_char_ptr = 1;
		}

		return ('?');
	}

	/* Option requires an argument? */

	if (*++opts_ptr == ':') {
		if (argv[acpi_gbl_optind][(int)(current_char_ptr + 1)] != '\0') {
			acpi_gbl_optarg =
			    &argv[acpi_gbl_optind++][(int)
						     (current_char_ptr + 1)];
		} else if (++acpi_gbl_optind >= argc) {
			ACPI_OPTION_ERROR("Option requires an argument: -",
					  current_char);

			current_char_ptr = 1;
			return ('?');
		} else {
			acpi_gbl_optarg = argv[acpi_gbl_optind++];
		}

		current_char_ptr = 1;
	}

	/* Option has an optional argument? */

	else if (*opts_ptr == '+') {
		if (argv[acpi_gbl_optind][(int)(current_char_ptr + 1)] != '\0') {
			acpi_gbl_optarg =
			    &argv[acpi_gbl_optind++][(int)
						     (current_char_ptr + 1)];
		} else if (++acpi_gbl_optind >= argc) {
			acpi_gbl_optarg = NULL;
		} else {
			acpi_gbl_optarg = argv[acpi_gbl_optind++];
		}

		current_char_ptr = 1;
	}

	/* Option has optional single-char arguments? */

	else if (*opts_ptr == '^') {
		if (argv[acpi_gbl_optind][(int)(current_char_ptr + 1)] != '\0') {
			acpi_gbl_optarg =
			    &argv[acpi_gbl_optind][(int)(current_char_ptr + 1)];
		} else {
			acpi_gbl_optarg = "^";
		}

		acpi_gbl_sub_opt_char = acpi_gbl_optarg[0];
		acpi_gbl_optind++;
		current_char_ptr = 1;
	}

	/* Option has a required single-char argument? */

	else if (*opts_ptr == '|') {
		if (argv[acpi_gbl_optind][(int)(current_char_ptr + 1)] != '\0') {
			acpi_gbl_optarg =
			    &argv[acpi_gbl_optind][(int)(current_char_ptr + 1)];
		} else {
			ACPI_OPTION_ERROR
			    ("Option requires a single-character suboption: -",
			     current_char);

			current_char_ptr = 1;
			return ('?');
		}

		acpi_gbl_sub_opt_char = acpi_gbl_optarg[0];
		acpi_gbl_optind++;
		current_char_ptr = 1;
	}

	/* Option with no arguments */

	else {
		if (argv[acpi_gbl_optind][++current_char_ptr] == '\0') {
			current_char_ptr = 1;
			acpi_gbl_optind++;
		}

		acpi_gbl_optarg = NULL;
	}

	return (current_char);
}