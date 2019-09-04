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
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fork () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_print_msg (char*) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*) ; 
 scalar_t__ mpid ; 
 scalar_t__ nerrs ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fork_wait(void)
{
	pid_t child = fork();
	if (child == 0) {
		nerrs = 0;
		return true;
	} else if (child > 0) {
		int status;
		if (waitpid(child, &status, 0) != child ||
		    !WIFEXITED(status)) {
			ksft_print_msg("Child died\n");
			nerrs++;
		} else if (WEXITSTATUS(status) != 0) {
			ksft_print_msg("Child failed\n");
			nerrs++;
		} else {
			/* don't print this message for mpid */
			if (getpid() != mpid)
				ksft_test_result_pass("Passed\n");
		}
		return false;
	} else {
		ksft_exit_fail_msg("fork - %s\n", strerror(errno));
		return false;
	}
}