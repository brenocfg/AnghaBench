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
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  scalar_t__ futex_t ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ FUTEX_INITIALIZER ; 
 int /*<<< orphan*/  FUTEX_PRIVATE_FLAG ; 
 int RET_FAIL ; 
 int RET_PASS ; 
 int /*<<< orphan*/  TEST_NAME ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basename (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fail (char*,scalar_t__,char*) ; 
 int futex_wait (scalar_t__*,scalar_t__,struct timespec*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  info (char*,scalar_t__,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  ksft_print_header () ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_set_plan (int) ; 
 int /*<<< orphan*/  log_color (int) ; 
 int /*<<< orphan*/  log_verbosity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  print_result (int /*<<< orphan*/ ,int) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  timeout_ns ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	struct timespec to = {.tv_sec = 0, .tv_nsec = timeout_ns};
	futex_t f1 = FUTEX_INITIALIZER;
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
	ksft_print_msg("%s: Test the unexpected futex value in FUTEX_WAIT\n",
	       basename(argv[0]));

	info("Calling futex_wait on f1: %u @ %p with val=%u\n", f1, &f1, f1+1);
	res = futex_wait(&f1, f1+1, &to, FUTEX_PRIVATE_FLAG);
	if (!res || errno != EWOULDBLOCK) {
		fail("futex_wait returned: %d %s\n",
		     res ? errno : res, res ? strerror(errno) : "");
		ret = RET_FAIL;
	}

	print_result(TEST_NAME, ret);
	return ret;
}