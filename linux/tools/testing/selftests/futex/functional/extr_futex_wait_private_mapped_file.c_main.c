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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int RET_ERROR ; 
 int RET_FAIL ; 
 int RET_PASS ; 
 int /*<<< orphan*/  TEST_NAME ; 
 int /*<<< orphan*/  WAKE_WAIT_US ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int futex_wake (int*,int,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/  ksft_print_header () ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_set_plan (int) ; 
 int /*<<< orphan*/  log_color (int) ; 
 int /*<<< orphan*/  log_verbosity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  print_result (int /*<<< orphan*/ ,int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  thr_futex_wait ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int /*<<< orphan*/ ) ; 
 int val ; 

int main(int argc, char **argv)
{
	pthread_t thr;
	int ret = RET_PASS;
	int res;
	int c;

	while ((c = getopt(argc, argv, "chv:")) != -1) {
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
	ksft_print_msg(
		"%s: Test the futex value of private file mappings in FUTEX_WAIT\n",
		basename(argv[0]));

	ret = pthread_create(&thr, NULL, thr_futex_wait, NULL);
	if (ret < 0) {
		fprintf(stderr, "pthread_create error\n");
		ret = RET_ERROR;
		goto out;
	}

	info("wait a while\n");
	usleep(WAKE_WAIT_US);
	val = 2;
	res = futex_wake(&val, 1, 0);
	info("futex_wake %d\n", res);
	if (res != 1) {
		fail("FUTEX_WAKE didn't find the waiting thread.\n");
		ret = RET_FAIL;
	}

	info("join\n");
	pthread_join(thr, NULL);

 out:
	print_result(TEST_NAME, ret);
	return ret;
}