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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ERRS (char*,int /*<<< orphan*/ *) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/ * board ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * ofname ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ opterr ; 
 int optind ; 
 char* optopt ; 
 int parse_opt_block (int,int /*<<< orphan*/ ) ; 
 int parse_opt_board (int,int /*<<< orphan*/ ) ; 
 int parse_opt_ofname (int,int /*<<< orphan*/ ) ; 
 scalar_t__ process_blocks () ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (int) ; 
 int /*<<< orphan*/  verblevel ; 
 scalar_t__ write_out_image (int /*<<< orphan*/ *) ; 

int
main(int argc, char *argv[])
{
	int optinvalid = 0;   /* flag for invalid option */
	int c;
	int res = EXIT_FAILURE;

	FILE *outfile;

	progname=basename(argv[0]);

	opterr = 0;  /* could not print standard getopt error messages */
	while ( 1 ) {
		optinvalid = 0;

		c = getopt(argc, argv, "b:B:ho:r:v");
		if (c == -1)
			break;

		switch (c) {
		case 'b':
		case 'r':
			optinvalid = parse_opt_block(c,optarg);
			break;
		case 'B':
			optinvalid = parse_opt_board(c,optarg);
			break;
		case 'o':
			optinvalid = parse_opt_ofname(c,optarg);
			break;
		case 'v':
			verblevel++;
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		default:
			optinvalid = 1;
			break;
		}
		if (optinvalid != 0 ) {
			ERR("invalid option: -%c", optopt);
			goto out;
		}
	}

	if (board == NULL) {
		ERR("no board specified");
		goto out;
	}

	if (ofname == NULL) {
		ERR("no output file specified");
		goto out;
	}

	if (optind < argc) {
		ERR("invalid option: %s", argv[optind]);
		goto out;
	}

	if (process_blocks() != 0) {
		goto out;
	}

	outfile = fopen(ofname, "w");
	if (outfile == NULL) {
		ERRS("could not open \"%s\" for writing", ofname);
		goto out;
	}

	if (write_out_image(outfile) != 0)
		goto out_flush;

	DBG(1,"Image file %s completed.", ofname);

	res = EXIT_SUCCESS;

out_flush:
	fflush(outfile);
	fclose(outfile);
	if (res != EXIT_SUCCESS) {
		unlink(ofname);
	}
out:
	return res;
}