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
typedef  int /*<<< orphan*/  tracer_func_t ;
struct __test_metadata {int dummy; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_LE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PR_SET_PTRACER ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  __NR_exit ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  cont_handler ; 
 scalar_t__ fork () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  pipe (int*) ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int,char*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_tracer (struct __test_metadata*,int,scalar_t__,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

pid_t setup_trace_fixture(struct __test_metadata *_metadata,
			  tracer_func_t func, void *args, bool ptrace_syscall)
{
	char sync;
	int pipefd[2];
	pid_t tracer_pid;
	pid_t tracee = getpid();

	/* Setup a pipe for clean synchronization. */
	ASSERT_EQ(0, pipe(pipefd));

	/* Fork a child which we'll promote to tracer */
	tracer_pid = fork();
	ASSERT_LE(0, tracer_pid);
	signal(SIGALRM, cont_handler);
	if (tracer_pid == 0) {
		close(pipefd[0]);
		start_tracer(_metadata, pipefd[1], tracee, func, args,
			     ptrace_syscall);
		syscall(__NR_exit, 0);
	}
	close(pipefd[1]);
	prctl(PR_SET_PTRACER, tracer_pid, 0, 0, 0);
	read(pipefd[0], &sync, 1);
	close(pipefd[0]);

	return tracer_pid;
}