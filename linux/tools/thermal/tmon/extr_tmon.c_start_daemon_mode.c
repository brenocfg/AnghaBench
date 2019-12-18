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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int daemon_mode ; 
 int /*<<< orphan*/  disable_tui () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 scalar_t__ setsid () ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  umask (int) ; 

__attribute__((used)) static void start_daemon_mode()
{
	daemon_mode = 1;
	/* fork */
	pid_t	sid, pid = fork();
	if (pid < 0) {
		exit(EXIT_FAILURE);
	} else if (pid > 0)
		/* kill parent */
		exit(EXIT_SUCCESS);

	/* disable TUI, it may not be necessary, but saves some resource */
	disable_tui();

	/* change the file mode mask */
	umask(S_IWGRP | S_IWOTH);

	/* new SID for the daemon process */
	sid = setsid();
	if (sid < 0)
		exit(EXIT_FAILURE);

	/* change working directory */
	if ((chdir("/")) < 0)
		exit(EXIT_FAILURE);


	sleep(10);

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

}