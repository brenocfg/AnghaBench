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
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  ksft_exit_fail () ; 
 int /*<<< orphan*/  ksft_exit_pass () ; 
 int /*<<< orphan*/  ksft_print_header () ; 
 int /*<<< orphan*/  ksft_set_plan (int) ; 
 int /*<<< orphan*/  ksft_test_result_fail (char*,int,int,...) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*,int,int,...) ; 
 int run_test (int,int,int,int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigalrm ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
	int opt;
	bool succeeded = true;
	struct sigaction act;
	int wr, wp, size;
	bool result;

	ksft_print_header();
	ksft_set_plan(213);

	act.sa_handler = sigalrm;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, NULL);
	for (size = 1; size <= 32; size = size*2) {
		for (wr = 0; wr <= 32; wr = wr + size) {
			for (wp = wr - size; wp <= wr + size; wp = wp + size) {
				result = run_test(size, MIN(size, 8), wr, wp);
				if ((result && wr == wp) ||
				    (!result && wr != wp))
					ksft_test_result_pass(
						"Test size = %d write offset = %d watchpoint offset = %d\n",
						size, wr, wp);
				else {
					ksft_test_result_fail(
						"Test size = %d write offset = %d watchpoint offset = %d\n",
						size, wr, wp);
					succeeded = false;
				}
			}
		}
	}

	for (size = 1; size <= 32; size = size*2) {
		if (run_test(size, 8, -size, -8))
			ksft_test_result_pass(
				"Test size = %d write offset = %d watchpoint offset = -8\n",
				size, -size);
		else {
			ksft_test_result_fail(
				"Test size = %d write offset = %d watchpoint offset = -8\n",
				size, -size);
			succeeded = false;
		}
	}

	if (succeeded)
		ksft_exit_pass();
	else
		ksft_exit_fail();
}