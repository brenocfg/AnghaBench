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
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 scalar_t__ do_exec ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  iterations ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  run_exec () ; 
 int waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bench_fork(void)
{
	while (1) {
		pid_t pid = fork();
		if (pid == -1) {
			perror("fork");
			exit(1);
		}
		if (pid == 0) {
			if (do_exec)
				run_exec();
			_exit(0);
		}
		pid = waitpid(pid, NULL, 0);
		if (pid == -1) {
			perror("waitpid");
			exit(1);
		}
		iterations++;
	}
}