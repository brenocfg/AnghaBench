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
 int KSFT_SKIP ; 
 int NPROCESS ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*) ; 
 int /*<<< orphan*/  __WALL ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int get_warnings_count () ; 
 int /*<<< orphan*/  is_intel_cpu () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test () ; 
 scalar_t__ vm_is_unrestricted_guest (int /*<<< orphan*/ *) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int main(void)
{
	int warnings_before, warnings_after;

	if (!is_intel_cpu()) {
		printf("Must be run on an Intel CPU, skipping test\n");
		exit(KSFT_SKIP);
	}

	if (vm_is_unrestricted_guest(NULL)) {
		printf("Unrestricted guest must be disabled, skipping test\n");
		exit(KSFT_SKIP);
	}

	warnings_before = get_warnings_count();

	for (int i = 0; i < NPROCESS; ++i) {
		int status;
		int pid = fork();

		if (pid < 0)
			exit(1);
		if (pid == 0) {
			test();
			exit(0);
		}
		while (waitpid(pid, &status, __WALL) != pid)
			;
	}

	warnings_after = get_warnings_count();
	TEST_ASSERT(warnings_before == warnings_after,
		   "Warnings found in kernel.  Run 'dmesg' to inspect them.");

	return 0;
}