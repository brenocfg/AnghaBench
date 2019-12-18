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
 int /*<<< orphan*/  DBG (int,char*,char*) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ERRS (char*,char*) ; 
 int ERR_FATAL ; 
 int ERR_INVALID_IMAGE ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  WARN (char*,char*) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/ * board ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ invalid_causes_error ; 
 scalar_t__ keep_invalid_images ; 
 char* ofname ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ opterr ; 
 int optind ; 
 char* optopt ; 
 int parse_opt_board (int,int /*<<< orphan*/ ) ; 
 int parse_opt_image (int,int /*<<< orphan*/ ) ; 
 int process_images () ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  usage (int) ; 
 int /*<<< orphan*/  verblevel ; 
 scalar_t__ write_out_header (int /*<<< orphan*/ *) ; 
 scalar_t__ write_out_images (int /*<<< orphan*/ *) ; 

int
main(int argc, char *argv[])
{
	int optinvalid = 0;   /* flag for invalid option */
	int c;
	int res = ERR_FATAL;

	FILE *outfile;

	progname=basename(argv[0]);

	opterr = 0;  /* could not print standard getopt error messages */
	while ( 1 ) {
		optinvalid = 0;

		c = getopt(argc, argv, "B:C:dhK:r:vw:x:");
		if (c == -1)
			break;

		switch (c) {
		case 'B':
			optinvalid = parse_opt_board(c,optarg);
			break;
		case 'd':
			invalid_causes_error = 0;
			break;
		case 'C':
		case 'K':
			optinvalid = parse_opt_image(c,optarg);
			break;
		case 'k':
			keep_invalid_images = 1;
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
		if (optinvalid != 0 ){
			ERR("invalid option: -%c", optopt);
			goto out;
		}
	}

	if (board == NULL) {
		ERR("no board specified");
		goto out;
	}

	if (optind == argc) {
		ERR("no output file specified");
		goto out;
	}

	ofname = argv[optind++];

	if (optind < argc) {
		ERR("invalid option: %s", argv[optind]);
		goto out;
	}

	res = process_images();
	if (res == ERR_FATAL)
		goto out;

	if (res == ERR_INVALID_IMAGE) {
		if (invalid_causes_error)
			res = ERR_FATAL;

		if (keep_invalid_images == 0) {
			WARN("generation of invalid images \"%s\" disabled", ofname);
			goto out;
		}

		WARN("generating invalid image: \"%s\"", ofname);
	}

	outfile = fopen(ofname, "w");
	if (outfile == NULL) {
		ERRS("could not open \"%s\" for writing", ofname);
		res = ERR_FATAL;
		goto out;
	}

	if (write_out_header(outfile) != 0) {
		res = ERR_FATAL;
		goto out_flush;
	}

	if (write_out_images(outfile) != 0) {
		res = ERR_FATAL;
		goto out_flush;
	}

	if (write_out_header(outfile) != 0) {
		res = ERR_FATAL;
		goto out_flush;
	}

	DBG(1,"Image file %s completed.", ofname);

out_flush:
	fflush(outfile);
	fclose(outfile);
	if (res == ERR_FATAL) {
		unlink(ofname);
	}
out:
	if (res == ERR_FATAL)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}