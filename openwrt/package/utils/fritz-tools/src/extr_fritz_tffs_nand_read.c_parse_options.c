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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 void* mtddev ; 
 int /*<<< orphan*/ * name_filter ; 
 void* optarg ; 
 int print_all_key_names ; 
 int read_oob_sector_health ; 
 int show_all ; 
 int /*<<< orphan*/  stderr ; 
 int swap_bytes ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_options(int argc, char *argv[])
{
	while (1) {
		int c;

		c = getopt(argc, argv, "abd:hln:o");
		if (c == -1)
			break;

		switch (c) {
		case 'a':
			show_all = true;
			name_filter = NULL;
			print_all_key_names = false;
			break;
		case 'b':
			swap_bytes = 1;
			break;
		case 'd':
			mtddev = optarg;
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		case 'l':
			print_all_key_names = true;
			show_all = false;
			name_filter = NULL;
			break;
		case 'n':
			name_filter = optarg;
			show_all = false;
			print_all_key_names = false;
			break;
		case 'o':
			read_oob_sector_health = true;
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}
	}

	if (!mtddev) {
		fprintf(stderr, "ERROR: No input file (-d <file>) given!\n");
		usage(EXIT_FAILURE);
	}

	if (!show_all && !name_filter && !print_all_key_names) {
		fprintf(stderr,
			"ERROR: either -l, -a or -n <key name> is required!\n");
		usage(EXIT_FAILURE);
	}
}