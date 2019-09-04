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
union pipe {int /*<<< orphan*/  fds; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  SIGKILL ; 
 int bind_to_cpu (int) ; 
 int /*<<< orphan*/  eat_cpu_child (union pipe,union pipe) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int getpid () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int pick_online_cpu () ; 
 int pipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ sync_with_child (union pipe,union pipe) ; 

pid_t eat_cpu(int (test_function)(void))
{
	union pipe read_pipe, write_pipe;
	int cpu, rc;
	pid_t pid;

	cpu = pick_online_cpu();
	FAIL_IF(cpu < 0);
	FAIL_IF(bind_to_cpu(cpu));

	if (pipe(read_pipe.fds) == -1)
		return -1;

	if (pipe(write_pipe.fds) == -1)
		return -1;

	pid = fork();
	if (pid == 0)
		exit(eat_cpu_child(write_pipe, read_pipe));

	if (sync_with_child(read_pipe, write_pipe)) {
		rc = -1;
		goto out;
	}

	printf("main test running as pid %d\n", getpid());

	rc = test_function();
out:
	kill(pid, SIGKILL);

	return rc;
}