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
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 unsigned long get_dscr () ; 
 unsigned long get_dscr_usr () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  set_dscr (unsigned long) ; 
 int /*<<< orphan*/  set_dscr_usr (unsigned long) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int dscr_inherit(void)
{
	unsigned long i, dscr = 0;
	pid_t pid;

	srand(getpid());
	set_dscr(dscr);

	for (i = 0; i < COUNT; i++) {
		unsigned long cur_dscr, cur_dscr_usr;

		dscr++;
		if (dscr > DSCR_MAX)
			dscr = 0;

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
			cur_dscr = get_dscr();
			if (cur_dscr != dscr) {
				fprintf(stderr, "Kernel DSCR should be %ld "
					"but is %ld\n", dscr, cur_dscr);
				exit(1);
			}

			cur_dscr_usr = get_dscr_usr();
			if (cur_dscr_usr != dscr) {
				fprintf(stderr, "User DSCR should be %ld "
					"but is %ld\n", dscr, cur_dscr_usr);
				exit(1);
			}
			exit(0);
		}
	}
	return 0;
}