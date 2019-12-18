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
typedef  union perf_event {int dummy; } perf_event ;
struct perf_tool {int dummy; } ;
struct machine {char* root_dir; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  perf_event__handler_t ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ machine__is_default_guest (struct machine*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 scalar_t__ perf_event__prepare_comm (union perf_event*,int,struct machine*,int*,int*) ; 
 int perf_event__synthesize_comm (struct perf_tool*,union perf_event*,int,int /*<<< orphan*/ ,struct machine*) ; 
 scalar_t__ perf_event__synthesize_fork (struct perf_tool*,union perf_event*,int,int,int,int /*<<< orphan*/ ,struct machine*) ; 
 int perf_event__synthesize_mmap_events (struct perf_tool*,union perf_event*,int,int,int /*<<< orphan*/ ,struct machine*,int) ; 
 scalar_t__ perf_event__synthesize_namespaces (struct perf_tool*,union perf_event*,int,int,int /*<<< orphan*/ ,struct machine*) ; 
 scalar_t__ perf_tool__process_synth_event (struct perf_tool*,union perf_event*,struct machine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int strtol (int /*<<< orphan*/ ,char**,int) ; 

__attribute__((used)) static int __event__synthesize_thread(union perf_event *comm_event,
				      union perf_event *mmap_event,
				      union perf_event *fork_event,
				      union perf_event *namespaces_event,
				      pid_t pid, int full, perf_event__handler_t process,
				      struct perf_tool *tool, struct machine *machine, bool mmap_data)
{
	char filename[PATH_MAX];
	DIR *tasks;
	struct dirent *dirent;
	pid_t tgid, ppid;
	int rc = 0;

	/* special case: only send one comm event using passed in pid */
	if (!full) {
		tgid = perf_event__synthesize_comm(tool, comm_event, pid,
						   process, machine);

		if (tgid == -1)
			return -1;

		if (perf_event__synthesize_namespaces(tool, namespaces_event, pid,
						      tgid, process, machine) < 0)
			return -1;

		/*
		 * send mmap only for thread group leader
		 * see thread__init_map_groups
		 */
		if (pid == tgid &&
		    perf_event__synthesize_mmap_events(tool, mmap_event, pid, tgid,
						       process, machine, mmap_data))
			return -1;

		return 0;
	}

	if (machine__is_default_guest(machine))
		return 0;

	snprintf(filename, sizeof(filename), "%s/proc/%d/task",
		 machine->root_dir, pid);

	tasks = opendir(filename);
	if (tasks == NULL) {
		pr_debug("couldn't open %s\n", filename);
		return 0;
	}

	while ((dirent = readdir(tasks)) != NULL) {
		char *end;
		pid_t _pid;

		_pid = strtol(dirent->d_name, &end, 10);
		if (*end)
			continue;

		rc = -1;
		if (perf_event__prepare_comm(comm_event, _pid, machine,
					     &tgid, &ppid) != 0)
			break;

		if (perf_event__synthesize_fork(tool, fork_event, _pid, tgid,
						ppid, process, machine) < 0)
			break;

		if (perf_event__synthesize_namespaces(tool, namespaces_event, _pid,
						      tgid, process, machine) < 0)
			break;

		/*
		 * Send the prepared comm event
		 */
		if (perf_tool__process_synth_event(tool, comm_event, machine, process) != 0)
			break;

		rc = 0;
		if (_pid == pid) {
			/* process the parent's maps too */
			rc = perf_event__synthesize_mmap_events(tool, mmap_event, pid, tgid,
						process, machine, mmap_data);
			if (rc)
				break;
		}
	}

	closedir(tasks);
	return rc;
}