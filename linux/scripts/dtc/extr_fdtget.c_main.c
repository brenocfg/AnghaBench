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
struct display_info {int size; int /*<<< orphan*/  default_val; int /*<<< orphan*/  mode; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  disp ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_LIST_PROPS ; 
 int /*<<< orphan*/  MODE_LIST_SUBNODES ; 
 int /*<<< orphan*/  MODE_SHOW_VALUE ; 
 scalar_t__ do_fdtget (struct display_info*,char*,char**,int,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memset (struct display_info*,char,int) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  usage (char*) ; 
 int /*<<< orphan*/  utilfdt_decode_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

int main(int argc, char *argv[])
{
	char *filename = NULL;
	struct display_info disp;
	int args_per_step = 2;

	/* set defaults */
	memset(&disp, '\0', sizeof(disp));
	disp.size = -1;
	disp.mode = MODE_SHOW_VALUE;
	for (;;) {
		int c = getopt(argc, argv, "d:hlpt:");
		if (c == -1)
			break;

		switch (c) {
		case 'h':
		case '?':
			usage(NULL);

		case 't':
			if (utilfdt_decode_type(optarg, &disp.type,
					&disp.size))
				usage("Invalid type string");
			break;

		case 'p':
			disp.mode = MODE_LIST_PROPS;
			args_per_step = 1;
			break;

		case 'l':
			disp.mode = MODE_LIST_SUBNODES;
			args_per_step = 1;
			break;

		case 'd':
			disp.default_val = optarg;
			break;
		}
	}

	if (optind < argc)
		filename = argv[optind++];
	if (!filename)
		usage("Missing filename");

	argv += optind;
	argc -= optind;

	/* Allow no arguments, and silently succeed */
	if (!argc)
		return 0;

	/* Check for node, property arguments */
	if (args_per_step == 2 && (argc % 2))
		usage("Must have an even number of arguments");

	if (do_fdtget(&disp, filename, argv, argc, args_per_step))
		return 1;
	return 0;
}