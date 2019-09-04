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
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  ksft_test_result_fail (char*,char*) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_test(int (*test)(void), char *name)
{
	int result;
	pid_t childpid;
	int ret;

	fflush(stdout);
	childpid = fork();

	if (childpid) {
		waitpid(childpid, &result, 0);
		if (WIFEXITED(result)) {
			ret = WEXITSTATUS(result);
			if (!ret)
				ksft_test_result_pass("[RUN]\t%s\n", name);
			else
				ksft_test_result_fail("[RUN]\t%s\n", name);
			return ret;
		}
		return 1;
	}

	exit(test());
}