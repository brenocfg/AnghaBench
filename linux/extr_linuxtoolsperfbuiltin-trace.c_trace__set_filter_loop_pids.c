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
struct trace {int /*<<< orphan*/  evlist; int /*<<< orphan*/  host; } ;
struct thread {int /*<<< orphan*/  tid; int /*<<< orphan*/  ppid; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpid () ; 
 struct thread* machine__find_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int perf_evlist__set_filter_pids (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  thread__comm_str (struct thread*) ; 

__attribute__((used)) static int trace__set_filter_loop_pids(struct trace *trace)
{
	unsigned int nr = 1;
	pid_t pids[32] = {
		getpid(),
	};
	struct thread *thread = machine__find_thread(trace->host, pids[0], pids[0]);

	while (thread && nr < ARRAY_SIZE(pids)) {
		struct thread *parent = machine__find_thread(trace->host, thread->ppid, thread->ppid);

		if (parent == NULL)
			break;

		if (!strcmp(thread__comm_str(parent), "sshd")) {
			pids[nr++] = parent->tid;
			break;
		}
		thread = parent;
	}

	return perf_evlist__set_filter_pids(trace->evlist, nr, pids);
}