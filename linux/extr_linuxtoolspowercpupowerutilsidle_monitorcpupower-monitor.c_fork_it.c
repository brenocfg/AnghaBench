#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
typedef  int pid_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) () ;int /*<<< orphan*/  (* start ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 char* _ (char*) ; 
 unsigned int avail_monitors ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 TYPE_1__** monitors ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned long long,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 unsigned long long timespec_diff_us (struct timespec,struct timespec) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int fork_it(char **argv)
{
	int status;
	unsigned int num;
	unsigned long long timediff;
	pid_t child_pid;
	struct timespec start, end;

	child_pid = fork();
	clock_gettime(CLOCK_REALTIME, &start);

	for (num = 0; num < avail_monitors; num++)
		monitors[num]->start();

	if (!child_pid) {
		/* child */
		execvp(argv[0], argv);
	} else {
		/* parent */
		if (child_pid == -1) {
			perror("fork");
			exit(1);
		}

		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (waitpid(child_pid, &status, 0) == -1) {
			perror("wait");
			exit(1);
		}
	}
	clock_gettime(CLOCK_REALTIME, &end);
	for (num = 0; num < avail_monitors; num++)
		monitors[num]->stop();

	timediff = timespec_diff_us(start, end);
	if (WIFEXITED(status))
		printf(_("%s took %.5f seconds and exited with status %d\n"),
			argv[0], timediff / (1000.0 * 1000),
			WEXITSTATUS(status));
	return 0;
}