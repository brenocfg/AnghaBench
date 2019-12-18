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
struct task_desc {int /*<<< orphan*/  nr_events; int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; int /*<<< orphan*/  nr; } ;
struct perf_sched {unsigned long nr_tasks; struct task_desc** tasks; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_task_traces(struct perf_sched *sched)
{
	struct task_desc *task;
	unsigned long i;

	for (i = 0; i < sched->nr_tasks; i++) {
		task = sched->tasks[i];
		printf("task %6ld (%20s:%10ld), nr_events: %ld\n",
			task->nr, task->comm, task->pid, task->nr_events);
	}
}