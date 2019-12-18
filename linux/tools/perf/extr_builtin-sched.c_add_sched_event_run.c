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
typedef  scalar_t__ u64 ;
struct task_desc {int dummy; } ;
struct sched_atom {scalar_t__ type; scalar_t__ duration; } ;
struct perf_sched {int /*<<< orphan*/  nr_run_events; int /*<<< orphan*/  nr_run_events_optimized; } ;

/* Variables and functions */
 scalar_t__ SCHED_EVENT_RUN ; 
 struct sched_atom* get_new_event (struct task_desc*,scalar_t__) ; 
 struct sched_atom* last_event (struct task_desc*) ; 

__attribute__((used)) static void add_sched_event_run(struct perf_sched *sched, struct task_desc *task,
				u64 timestamp, u64 duration)
{
	struct sched_atom *event, *curr_event = last_event(task);

	/*
	 * optimize an existing RUN event by merging this one
	 * to it:
	 */
	if (curr_event && curr_event->type == SCHED_EVENT_RUN) {
		sched->nr_run_events_optimized++;
		curr_event->duration += duration;
		return;
	}

	event = get_new_event(task, timestamp);

	event->type = SCHED_EVENT_RUN;
	event->duration = duration;

	sched->nr_run_events++;
}