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
struct task_desc {unsigned long pid; size_t nr; int /*<<< orphan*/  comm; } ;
struct perf_sched {size_t nr_tasks; struct task_desc** tasks; struct task_desc** pid_to_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_PID ; 
 int /*<<< orphan*/  add_sched_event_sleep (struct perf_sched*,struct task_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct task_desc** calloc (int,int) ; 
 int /*<<< orphan*/  printf (char*,int,unsigned long,char const*) ; 
 void* realloc (struct task_desc**,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ sysctl__read_int (char*,int*) ; 
 scalar_t__ verbose ; 
 struct task_desc* zalloc (int) ; 

__attribute__((used)) static struct task_desc *register_pid(struct perf_sched *sched,
				      unsigned long pid, const char *comm)
{
	struct task_desc *task;
	static int pid_max;

	if (sched->pid_to_task == NULL) {
		if (sysctl__read_int("kernel/pid_max", &pid_max) < 0)
			pid_max = MAX_PID;
		BUG_ON((sched->pid_to_task = calloc(pid_max, sizeof(struct task_desc *))) == NULL);
	}
	if (pid >= (unsigned long)pid_max) {
		BUG_ON((sched->pid_to_task = realloc(sched->pid_to_task, (pid + 1) *
			sizeof(struct task_desc *))) == NULL);
		while (pid >= (unsigned long)pid_max)
			sched->pid_to_task[pid_max++] = NULL;
	}

	task = sched->pid_to_task[pid];

	if (task)
		return task;

	task = zalloc(sizeof(*task));
	task->pid = pid;
	task->nr = sched->nr_tasks;
	strcpy(task->comm, comm);
	/*
	 * every task starts in sleeping state - this gets ignored
	 * if there's no wakeup pointing to this sleep state:
	 */
	add_sched_event_sleep(sched, task, 0, 0);

	sched->pid_to_task[pid] = task;
	sched->nr_tasks++;
	sched->tasks = realloc(sched->tasks, sched->nr_tasks * sizeof(struct task_desc *));
	BUG_ON(!sched->tasks);
	sched->tasks[task->nr] = task;

	if (verbose > 0)
		printf("registered task #%ld, PID %ld (%s)\n", sched->nr_tasks, pid, comm);

	return task;
}