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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 char* ACPI_COMMON_BUILD_TIME ; 
 char* ACPI_COMMON_SIGNON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_OPT_END ; 
 int /*<<< orphan*/  AP_DUMP_ALL_TABLES ; 
 int /*<<< orphan*/  AP_DUMP_TABLE_BY_ADDRESS ; 
 int /*<<< orphan*/  AP_DUMP_TABLE_BY_FILE ; 
 int /*<<< orphan*/  AP_DUMP_TABLE_BY_NAME ; 
 int /*<<< orphan*/  AP_SUPPORTED_OPTIONS ; 
 int /*<<< orphan*/  AP_UTILITY_NAME ; 
 void* FALSE ; 
 void* TRUE ; 
 void* acpi_gbl_do_not_use_xsdt ; 
 char* acpi_gbl_optarg ; 
 int acpi_getopt (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_strtoul64 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ap_display_usage () ; 
 scalar_t__ ap_insert_action (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_open_output_file (char*) ; 
 scalar_t__ current_action ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 void* gbl_binary_mode ; 
 void* gbl_do_not_dump_xsdt ; 
 void* gbl_dump_customized_tables ; 
 int /*<<< orphan*/  gbl_rsdp_base ; 
 void* gbl_summary_mode ; 
 void* gbl_verbose_mode ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int ap_do_options(int argc, char **argv)
{
	int j;
	acpi_status status;

	/* Command line options */

	while ((j =
		acpi_getopt(argc, argv, AP_SUPPORTED_OPTIONS)) != ACPI_OPT_END)
		switch (j) {
			/*
			 * Global options
			 */
		case 'b':	/* Dump all input tables to binary files */

			gbl_binary_mode = TRUE;
			continue;

		case 'c':	/* Dump customized tables */

			if (!strcmp(acpi_gbl_optarg, "on")) {
				gbl_dump_customized_tables = TRUE;
			} else if (!strcmp(acpi_gbl_optarg, "off")) {
				gbl_dump_customized_tables = FALSE;
			} else {
				fprintf(stderr,
					"%s: Cannot handle this switch, please use on|off\n",
					acpi_gbl_optarg);
				return (-1);
			}
			continue;

		case 'h':
		case '?':

			ap_display_usage();
			return (1);

		case 'o':	/* Redirect output to a single file */

			if (ap_open_output_file(acpi_gbl_optarg)) {
				return (-1);
			}
			continue;

		case 'r':	/* Dump tables from specified RSDP */

			status =
			    acpi_ut_strtoul64(acpi_gbl_optarg, &gbl_rsdp_base);
			if (ACPI_FAILURE(status)) {
				fprintf(stderr,
					"%s: Could not convert to a physical address\n",
					acpi_gbl_optarg);
				return (-1);
			}
			continue;

		case 's':	/* Print table summaries only */

			gbl_summary_mode = TRUE;
			continue;

		case 'x':	/* Do not use XSDT */

			if (!acpi_gbl_do_not_use_xsdt) {
				acpi_gbl_do_not_use_xsdt = TRUE;
			} else {
				gbl_do_not_dump_xsdt = TRUE;
			}
			continue;

		case 'v':	/* -v: (Version): signon already emitted, just exit */

			switch (acpi_gbl_optarg[0]) {
			case '^':	/* -v: (Version) */

				fprintf(stderr,
					ACPI_COMMON_SIGNON(AP_UTILITY_NAME));
				return (1);

			case 'd':

				fprintf(stderr,
					ACPI_COMMON_SIGNON(AP_UTILITY_NAME));
				printf(ACPI_COMMON_BUILD_TIME);
				return (1);

			default:

				printf("Unknown option: -v%s\n",
				       acpi_gbl_optarg);
				return (-1);
			}
			break;

		case 'z':	/* Verbose mode */

			gbl_verbose_mode = TRUE;
			fprintf(stderr, ACPI_COMMON_SIGNON(AP_UTILITY_NAME));
			continue;

			/*
			 * Table options
			 */
		case 'a':	/* Get table by physical address */

			if (ap_insert_action
			    (acpi_gbl_optarg, AP_DUMP_TABLE_BY_ADDRESS)) {
				return (-1);
			}
			break;

		case 'f':	/* Get table from a file */

			if (ap_insert_action
			    (acpi_gbl_optarg, AP_DUMP_TABLE_BY_FILE)) {
				return (-1);
			}
			break;

		case 'n':	/* Get table by input name (signature) */

			if (ap_insert_action
			    (acpi_gbl_optarg, AP_DUMP_TABLE_BY_NAME)) {
				return (-1);
			}
			break;

		default:

			ap_display_usage();
			return (-1);
		}

	/* If there are no actions, this means "get/dump all tables" */

	if (current_action == 0) {
		if (ap_insert_action(NULL, AP_DUMP_ALL_TABLES)) {
			return (-1);
		}
	}

	return (0);
}