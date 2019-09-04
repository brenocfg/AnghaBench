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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int SIGTERM ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int child_pid ; 
 int getpid () ; 
 int /*<<< orphan*/  kill (int,int) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int signr ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sig_atexit(void)
{
	sigset_t set, oset;

	/*
	 * avoid race condition with SIGCHLD handler
	 * in skip_signal() which is modifying child_pid
	 * goal is to avoid send SIGTERM to a random
	 * process
	 */
	sigemptyset(&set);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_BLOCK, &set, &oset);

	if (child_pid != -1)
		kill(child_pid, SIGTERM);

	sigprocmask(SIG_SETMASK, &oset, NULL);

	if (signr == -1)
		return;

	signal(signr, SIG_DFL);
	kill(getpid(), signr);
}