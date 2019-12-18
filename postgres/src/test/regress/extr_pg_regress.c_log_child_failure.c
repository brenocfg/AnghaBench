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
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  pg_strsignal (int) ; 
 int /*<<< orphan*/  status (int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static void
log_child_failure(int exitstatus)
{
	if (WIFEXITED(exitstatus))
		status(_(" (test process exited with exit code %d)"),
			   WEXITSTATUS(exitstatus));
	else if (WIFSIGNALED(exitstatus))
	{
#if defined(WIN32)
		status(_(" (test process was terminated by exception 0x%X)"),
			   WTERMSIG(exitstatus));
#else
		status(_(" (test process was terminated by signal %d: %s)"),
			   WTERMSIG(exitstatus), pg_strsignal(WTERMSIG(exitstatus)));
#endif
	}
	else
		status(_(" (test process exited with unrecognized status %d)"),
			   exitstatus);
}