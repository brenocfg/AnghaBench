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
 int /*<<< orphan*/  TEST_NAME ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int broadcast ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  ksft_print_header () ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int,...) ; 
 int /*<<< orphan*/  ksft_set_plan (int) ; 
 int locked ; 
 int /*<<< orphan*/  log_color (int) ; 
 int /*<<< orphan*/  log_verbosity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int owner ; 
 int /*<<< orphan*/  print_result (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timeout_ns ; 
 int unit_test (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	int c, ret;

	while ((c = getopt(argc, argv, "bchlot:v:")) != -1) {
		switch (c) {
		case 'b':
			broadcast = 1;
			break;
		case 'c':
			log_color(1);
			break;
		case 'h':
			usage(basename(argv[0]));
			exit(0);
		case 'l':
			locked = 1;
			break;
		case 'o':
			owner = 1;
			locked = 0;
			break;
		case 't':
			timeout_ns = atoi(optarg);
			break;
		case 'v':
			log_verbosity(atoi(optarg));
			break;
		default:
			usage(basename(argv[0]));
			exit(1);
		}
	}

	ksft_print_header();
	ksft_set_plan(1);
	ksft_print_msg("%s: Test requeue functionality\n", basename(argv[0]));
	ksft_print_msg(
		"\tArguments: broadcast=%d locked=%d owner=%d timeout=%ldns\n",
		broadcast, locked, owner, timeout_ns);

	/*
	 * FIXME: unit_test is obsolete now that we parse options and the
	 * various style of runs are done by run.sh - simplify the code and move
	 * unit_test into main()
	 */
	ret = unit_test(broadcast, locked, owner, timeout_ns);

	print_result(TEST_NAME, ret);
	return ret;
}