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
typedef  int pid_t ;

/* Variables and functions */
 unsigned long COUNT ; 
 unsigned long DSCR_MAX ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  execlp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 unsigned long get_default_dscr () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  prog ; 
 int /*<<< orphan*/  set_dscr (unsigned long) ; 
 int /*<<< orphan*/  set_dscr_usr (unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  stderr ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int dscr_inherit_exec(void)
{
	unsigned long i, dscr = 0;
	pid_t pid;

	for (i = 0; i < COUNT; i++) {
		dscr++;
		if (dscr > DSCR_MAX)
			dscr = 0;

		if (dscr == get_default_dscr())
			continue;

		if (i % 2 == 0)
			set_dscr_usr(dscr);
		else
			set_dscr(dscr);

		pid = fork();
		if (pid == -1) {
			perror("fork() failed");
			exit(1);
		} else if (pid) {
			int status;

			if (waitpid(pid, &status, 0) == -1) {
				perror("waitpid() failed");
				exit(1);
			}

			if (!WIFEXITED(status)) {
				fprintf(stderr, "Child didn't exit cleanly\n");
				exit(1);
			}

			if (WEXITSTATUS(status) != 0) {
				fprintf(stderr, "Child didn't exit cleanly\n");
				return 1;
			}
		} else {
			char dscr_str[16];

			sprintf(dscr_str, "%ld", dscr);
			execlp(prog, prog, "exec", dscr_str, NULL);
			exit(1);
		}
	}
	return 0;
}