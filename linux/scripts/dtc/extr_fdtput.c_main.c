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
struct display_info {int size; scalar_t__ oper; int auto_path; int verbose; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  disp ;

/* Variables and functions */
 scalar_t__ OPER_CREATE_NODE ; 
 scalar_t__ OPER_WRITE_PROP ; 
 scalar_t__ do_fdtput (struct display_info*,char*,char**,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memset (struct display_info*,char,int) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  usage (char*) ; 
 int /*<<< orphan*/  utilfdt_decode_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

int main(int argc, char *argv[])
{
	struct display_info disp;
	char *filename = NULL;

	memset(&disp, '\0', sizeof(disp));
	disp.size = -1;
	disp.oper = OPER_WRITE_PROP;
	for (;;) {
		int c = getopt(argc, argv, "chpt:v");
		if (c == -1)
			break;

		/*
		 * TODO: add options to:
		 * - delete property
		 * - delete node (optionally recursively)
		 * - rename node
		 * - pack fdt before writing
		 * - set amount of free space when writing
		 * - expand fdt if value doesn't fit
		 */
		switch (c) {
		case 'c':
			disp.oper = OPER_CREATE_NODE;
			break;
		case 'h':
		case '?':
			usage(NULL);
		case 'p':
			disp.auto_path = 1;
			break;
		case 't':
			if (utilfdt_decode_type(optarg, &disp.type,
					&disp.size))
				usage("Invalid type string");
			break;

		case 'v':
			disp.verbose = 1;
			break;
		}
	}

	if (optind < argc)
		filename = argv[optind++];
	if (!filename)
		usage("Missing filename");

	argv += optind;
	argc -= optind;

	if (disp.oper == OPER_WRITE_PROP) {
		if (argc < 1)
			usage("Missing node");
		if (argc < 2)
			usage("Missing property");
	}

	if (do_fdtput(&disp, filename, argv, argc))
		return 1;
	return 0;
}