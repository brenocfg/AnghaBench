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
union pipe {int /*<<< orphan*/  fds; } ;
struct TYPE_2__ {int exclude_kernel; int exclude_hv; int exclude_idle; } ;
struct event {TYPE_1__ attr; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int ebb_event_enable (struct event*) ; 
 int /*<<< orphan*/  ebb_is_supported () ; 
 int /*<<< orphan*/  event_close (struct event*) ; 
 int /*<<< orphan*/  event_init_named (struct event*,int,char*) ; 
 int /*<<< orphan*/  event_leader_ebb_init (struct event*) ; 
 int event_open_with_pid (struct event*,scalar_t__) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int pipe (int /*<<< orphan*/ ) ; 
 int sync_with_child (union pipe,union pipe) ; 
 int /*<<< orphan*/  victim_child (union pipe,union pipe) ; 
 int wait_for_child (scalar_t__) ; 

int ebb_on_child(void)
{
	union pipe read_pipe, write_pipe;
	struct event event;
	pid_t pid;

	SKIP_IF(!ebb_is_supported());

	FAIL_IF(pipe(read_pipe.fds) == -1);
	FAIL_IF(pipe(write_pipe.fds) == -1);

	pid = fork();
	if (pid == 0) {
		/* NB order of pipes looks reversed */
		exit(victim_child(write_pipe, read_pipe));
	}

	FAIL_IF(sync_with_child(read_pipe, write_pipe));

	/* Child is running now */

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_open_with_pid(&event, pid));
	FAIL_IF(ebb_event_enable(&event));

	FAIL_IF(sync_with_child(read_pipe, write_pipe));

	/* Child should just exit happily */
	FAIL_IF(wait_for_child(pid));

	event_close(&event);

	return 0;
}