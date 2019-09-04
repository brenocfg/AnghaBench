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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  WNOHANG ; 
 scalar_t__ change_clocksource (char*) ; 
 char** clocksource_list ; 
 scalar_t__ fork () ; 
 int get_clocksources (char**) ; 
 int /*<<< orphan*/  get_cur_clocksource (char*,int) ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int run_tests (int) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

int main(int argv, char **argc)
{
	char orig_clk[512];
	int count, i, status;
	pid_t pid;

	get_cur_clocksource(orig_clk, 512);

	count = get_clocksources(clocksource_list);

	if (change_clocksource(clocksource_list[0])) {
		printf("Error: You probably need to run this as root\n");
		return -1;
	}

	/* Check everything is sane before we start switching asyncrhonously */
	for (i = 0; i < count; i++) {
		printf("Validating clocksource %s\n", clocksource_list[i]);
		if (change_clocksource(clocksource_list[i])) {
			status = -1;
			goto out;
		}
		if (run_tests(5)) {
			status = -1;
			goto out;
		}
	}


	printf("Running Asynchronous Switching Tests...\n");
	pid = fork();
	if (!pid)
		return run_tests(60);

	while (pid != waitpid(pid, &status, WNOHANG))
		for (i = 0; i < count; i++)
			if (change_clocksource(clocksource_list[i])) {
				status = -1;
				goto out;
			}
out:
	change_clocksource(orig_clk);

	if (status)
		return ksft_exit_fail();
	return ksft_exit_pass();
}