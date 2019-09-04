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
struct event {int dummy; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  ebb_child (union pipe,union pipe) ; 
 int /*<<< orphan*/  ebb_is_supported () ; 
 int event_disable (struct event*) ; 
 int event_read (struct event*) ; 
 int /*<<< orphan*/  event_report (struct event*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  kill_child_and_wait (scalar_t__) ; 
 int pipe (int /*<<< orphan*/ ) ; 
 int setup_child_event (struct event*,scalar_t__) ; 
 int sync_with_child (union pipe,union pipe) ; 
 int wait_for_child (scalar_t__) ; 

int task_event_vs_ebb(void)
{
	union pipe read_pipe, write_pipe;
	struct event event;
	pid_t pid;
	int rc;

	SKIP_IF(!ebb_is_supported());

	FAIL_IF(pipe(read_pipe.fds) == -1);
	FAIL_IF(pipe(write_pipe.fds) == -1);

	pid = fork();
	if (pid == 0) {
		/* NB order of pipes looks reversed */
		exit(ebb_child(write_pipe, read_pipe));
	}

	/* We setup the task event first */
	rc = setup_child_event(&event, pid);
	if (rc) {
		kill_child_and_wait(pid);
		return rc;
	}

	/* Signal the child to install its EBB event and wait */
	if (sync_with_child(read_pipe, write_pipe))
		/* If it fails, wait for it to exit */
		goto wait;

	/* Signal the child to run */
	FAIL_IF(sync_with_child(read_pipe, write_pipe));

wait:
	/* The EBB event should push the task event off so the child should succeed */
	FAIL_IF(wait_for_child(pid));
	FAIL_IF(event_disable(&event));
	FAIL_IF(event_read(&event));

	event_report(&event);

	/* The task event may have run, or not so we can't assert anything about it */

	return 0;
}