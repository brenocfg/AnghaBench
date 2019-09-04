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
typedef  int /*<<< orphan*/  u64 ;
struct task_desc {unsigned long nr_events; struct sched_atom** atoms; } ;
struct sched_atom {unsigned long nr; int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct sched_atom** realloc (struct sched_atom**,size_t) ; 
 struct sched_atom* zalloc (int) ; 

__attribute__((used)) static struct sched_atom *
get_new_event(struct task_desc *task, u64 timestamp)
{
	struct sched_atom *event = zalloc(sizeof(*event));
	unsigned long idx = task->nr_events;
	size_t size;

	event->timestamp = timestamp;
	event->nr = idx;

	task->nr_events++;
	size = sizeof(struct sched_atom *) * task->nr_events;
	task->atoms = realloc(task->atoms, size);
	BUG_ON(!task->atoms);

	task->atoms[idx] = event;

	return event;
}