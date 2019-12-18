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
struct timespec {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  futex_t ;

/* Variables and functions */
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  FUTEX_INITIALIZER ; 
 int /*<<< orphan*/  FUTEX_PRIVATE_FLAG ; 
 int RET_FAIL ; 
 int RET_PASS ; 
 int /*<<< orphan*/  TEST_NAME ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basename (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fail (char*,scalar_t__) ; 
 int futex_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksft_print_header () ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_set_plan (int) ; 
 int /*<<< orphan*/  log_color (int) ; 
 int /*<<< orphan*/  log_verbosity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  print_result (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timeout_ns ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	futex_t f1 = FUTEX_INITIALIZER;
	struct timespec to;
	int res, ret = RET_PASS;
	int c;

	while ((c = getopt(argc, argv, "cht:v:")) != -1) {
		switch (c) {
		case 'c':
			log_color(1);
			break;
		case 'h':
			usage(basename(argv[0]));
			exit(0);
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
	ksft_print_msg("%s: Block on a futex and wait for timeout\n",
	       basename(argv[0]));
	ksft_print_msg("\tArguments: timeout=%ldns\n", timeout_ns);

	/* initialize timeout */
	to.tv_sec = 0;
	to.tv_nsec = timeout_ns;

	info("Calling futex_wait on f1: %u @ %p\n", f1, &f1);
	res = futex_wait(&f1, f1, &to, FUTEX_PRIVATE_FLAG);
	if (!res || errno != ETIMEDOUT) {
		fail("futex_wait returned %d\n", ret < 0 ? errno : ret);
		ret = RET_FAIL;
	}

	print_result(TEST_NAME, ret);
	return ret;
}