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
typedef  int /*<<< orphan*/  cpu_set_t ;
typedef  int /*<<< orphan*/  available_cpus ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int CPU_SETSIZE ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  ksft_exit_fail () ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*) ; 
 int /*<<< orphan*/  ksft_exit_pass () ; 
 int /*<<< orphan*/  ksft_print_header () ; 
 int /*<<< orphan*/  ksft_set_plan (unsigned int) ; 
 int /*<<< orphan*/  ksft_test_result_fail (char*,int) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int run_test (int) ; 
 int sched_getaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  suspend () ; 

int main(int argc, char **argv)
{
	int opt;
	bool do_suspend = true;
	bool succeeded = true;
	unsigned int tests = 0;
	cpu_set_t available_cpus;
	int err;
	int cpu;

	ksft_print_header();

	while ((opt = getopt(argc, argv, "n")) != -1) {
		switch (opt) {
		case 'n':
			do_suspend = false;
			break;
		default:
			printf("Usage: %s [-n]\n", argv[0]);
			printf("        -n: do not trigger a suspend/resume cycle before the test\n");
			return -1;
		}
	}

	for (cpu = 0; cpu < CPU_SETSIZE; cpu++) {
		if (!CPU_ISSET(cpu, &available_cpus))
			continue;
		tests++;
	}
	ksft_set_plan(tests);

	if (do_suspend)
		suspend();

	err = sched_getaffinity(0, sizeof(available_cpus), &available_cpus);
	if (err < 0)
		ksft_exit_fail_msg("sched_getaffinity() failed\n");

	for (cpu = 0; cpu < CPU_SETSIZE; cpu++) {
		bool test_success;

		if (!CPU_ISSET(cpu, &available_cpus))
			continue;

		test_success = run_test(cpu);
		if (test_success) {
			ksft_test_result_pass("CPU %d\n", cpu);
		} else {
			ksft_test_result_fail("CPU %d\n", cpu);
			succeeded = false;
		}
	}

	if (succeeded)
		ksft_exit_pass();
	else
		ksft_exit_fail();
}