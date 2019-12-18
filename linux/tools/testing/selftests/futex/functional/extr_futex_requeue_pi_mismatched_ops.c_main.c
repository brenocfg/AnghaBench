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
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  FUTEX_PRIVATE_FLAG ; 
 int RET_ERROR ; 
 int RET_FAIL ; 
 int RET_PASS ; 
 int /*<<< orphan*/  TEST_NAME ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  blocking_child ; 
 int child_ret ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  f1 ; 
 int /*<<< orphan*/  f2 ; 
 int /*<<< orphan*/  fail (char*) ; 
 int futex_cmp_requeue_pi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int futex_wake (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  ksft_print_header () ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_set_plan (int) ; 
 int /*<<< orphan*/  log_color (int) ; 
 int /*<<< orphan*/  log_verbosity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  print_result (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	int ret = RET_PASS;
	pthread_t child;
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
	ksft_print_msg("%s: Detect mismatched requeue_pi operations\n",
	       basename(argv[0]));

	if (pthread_create(&child, NULL, blocking_child, NULL)) {
		error("pthread_create\n", errno);
		ret = RET_ERROR;
		goto out;
	}
	/* Allow the child to block in the kernel. */
	sleep(1);

	/*
	 * The kernel should detect the waiter did not setup the
	 * q->requeue_pi_key and return -EINVAL. If it does not,
	 * it likely gave the lock to the child, which is now hung
	 * in the kernel.
	 */
	ret = futex_cmp_requeue_pi(&f1, f1, &f2, 1, 0, FUTEX_PRIVATE_FLAG);
	if (ret < 0) {
		if (errno == EINVAL) {
			/*
			 * The kernel correctly detected the mismatched
			 * requeue_pi target and aborted. Wake the child with
			 * FUTEX_WAKE.
			 */
			ret = futex_wake(&f1, 1, FUTEX_PRIVATE_FLAG);
			if (ret == 1) {
				ret = RET_PASS;
			} else if (ret < 0) {
				error("futex_wake\n", errno);
				ret = RET_ERROR;
			} else {
				error("futex_wake did not wake the child\n", 0);
				ret = RET_ERROR;
			}
		} else {
			error("futex_cmp_requeue_pi\n", errno);
			ret = RET_ERROR;
		}
	} else if (ret > 0) {
		fail("futex_cmp_requeue_pi failed to detect the mismatch\n");
		ret = RET_FAIL;
	} else {
		error("futex_cmp_requeue_pi found no waiters\n", 0);
		ret = RET_ERROR;
	}

	pthread_join(child, NULL);

	if (!ret)
		ret = child_ret;

 out:
	/* If the kernel crashes, we shouldn't return at all. */
	print_result(TEST_NAME, ret);
	return ret;
}