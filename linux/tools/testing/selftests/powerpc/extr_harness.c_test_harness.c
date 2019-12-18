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
 int /*<<< orphan*/  GIT_VERSION ; 
 int MAGIC_SKIP_RETURN_VALUE ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  perror (char*) ; 
 int run_test (int (*) (),char*) ; 
 int /*<<< orphan*/  sig_action ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_error (char*) ; 
 int /*<<< orphan*/  test_finish (char*,int) ; 
 int /*<<< orphan*/  test_set_git_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_skip (char*) ; 
 int /*<<< orphan*/  test_start (char*) ; 

int test_harness(int (test_function)(void), char *name)
{
	int rc;

	test_start(name);
	test_set_git_version(GIT_VERSION);

	if (sigaction(SIGINT, &sig_action, NULL)) {
		perror("sigaction (sigint)");
		test_error(name);
		return 1;
	}

	if (sigaction(SIGALRM, &sig_action, NULL)) {
		perror("sigaction (sigalrm)");
		test_error(name);
		return 1;
	}

	rc = run_test(test_function, name);

	if (rc == MAGIC_SKIP_RETURN_VALUE) {
		test_skip(name);
		/* so that skipped test is not marked as failed */
		rc = 0;
	} else
		test_finish(name, rc);

	return rc;
}