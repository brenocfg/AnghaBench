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
typedef  int /*<<< orphan*/  pgpid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ kill (int,int /*<<< orphan*/ ) ; 
 int postmasterPID ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_stderr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
trap_sigint_during_startup(int sig)
{
	if (postmasterPID != -1)
	{
		if (kill(postmasterPID, SIGINT) != 0)
			write_stderr(_("%s: could not send stop signal (PID: %ld): %s\n"),
						 progname, (pgpid_t) postmasterPID, strerror(errno));
	}

	/*
	 * Clear the signal handler, and send the signal again, to terminate the
	 * process as normal.
	 */
	pqsignal(SIGINT, SIG_DFL);
	raise(SIGINT);
}