#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* type; int (* handler ) (char*) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LINE_SIZE ; 
 int /*<<< orphan*/  cpio_trailer () ; 
 int /*<<< orphan*/  default_mtime ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* file_handler_table ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  strtol (char*,char**,int) ; 
 int stub1 (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main (int argc, char *argv[])
{
	FILE *cpio_list;
	char line[LINE_SIZE];
	char *args, *type;
	int ec = 0;
	int line_nr = 0;
	const char *filename;

	default_mtime = time(NULL);
	while (1) {
		int opt = getopt(argc, argv, "t:h");
		char *invalid;

		if (opt == -1)
			break;
		switch (opt) {
		case 't':
			default_mtime = strtol(optarg, &invalid, 10);
			if (!*optarg || *invalid) {
				fprintf(stderr, "Invalid timestamp: %s\n",
						optarg);
				usage(argv[0]);
				exit(1);
			}
			break;
		case 'h':
		case '?':
			usage(argv[0]);
			exit(opt == 'h' ? 0 : 1);
		}
	}

	if (argc - optind != 1) {
		usage(argv[0]);
		exit(1);
	}
	filename = argv[optind];
	if (!strcmp(filename, "-"))
		cpio_list = stdin;
	else if (!(cpio_list = fopen(filename, "r"))) {
		fprintf(stderr, "ERROR: unable to open '%s': %s\n\n",
			filename, strerror(errno));
		usage(argv[0]);
		exit(1);
	}

	while (fgets(line, LINE_SIZE, cpio_list)) {
		int type_idx;
		size_t slen = strlen(line);

		line_nr++;

		if ('#' == *line) {
			/* comment - skip to next line */
			continue;
		}

		if (! (type = strtok(line, " \t"))) {
			fprintf(stderr,
				"ERROR: incorrect format, could not locate file type line %d: '%s'\n",
				line_nr, line);
			ec = -1;
			break;
		}

		if ('\n' == *type) {
			/* a blank line */
			continue;
		}

		if (slen == strlen(type)) {
			/* must be an empty line */
			continue;
		}

		if (! (args = strtok(NULL, "\n"))) {
			fprintf(stderr,
				"ERROR: incorrect format, newline required line %d: '%s'\n",
				line_nr, line);
			ec = -1;
		}

		for (type_idx = 0; file_handler_table[type_idx].type; type_idx++) {
			int rc;
			if (! strcmp(line, file_handler_table[type_idx].type)) {
				if ((rc = file_handler_table[type_idx].handler(args))) {
					ec = rc;
					fprintf(stderr, " line %d\n", line_nr);
				}
				break;
			}
		}

		if (NULL == file_handler_table[type_idx].type) {
			fprintf(stderr, "unknown file type line %d: '%s'\n",
				line_nr, line);
		}
	}
	if (ec == 0)
		cpio_trailer();

	exit(ec);
}