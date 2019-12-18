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
struct TYPE_2__ {unsigned int* map_pid_to_cmdline; } ;

/* Variables and functions */
 unsigned int NO_CMDLINE_MAP ; 
 int PID_MAX_DEFAULT ; 
 int /*<<< orphan*/  TASK_COMM_LEN ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  get_saved_cmdlines (unsigned int) ; 
 TYPE_1__* savedcmd ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __trace_find_cmdline(int pid, char comm[])
{
	unsigned map;

	if (!pid) {
		strcpy(comm, "<idle>");
		return;
	}

	if (WARN_ON_ONCE(pid < 0)) {
		strcpy(comm, "<XXX>");
		return;
	}

	if (pid > PID_MAX_DEFAULT) {
		strcpy(comm, "<...>");
		return;
	}

	map = savedcmd->map_pid_to_cmdline[pid];
	if (map != NO_CMDLINE_MAP)
		strlcpy(comm, get_saved_cmdlines(map), TASK_COMM_LEN);
	else
		strcpy(comm, "<...>");
}