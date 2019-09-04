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
struct stop_event_data {struct perf_event* event; } ;
struct ring_buffer {int dummy; } ;
struct remote_output {int /*<<< orphan*/  err; struct ring_buffer* rb; } ;
struct perf_event {int /*<<< orphan*/  rb; struct perf_event* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_event_stop (struct stop_event_data*) ; 
 int /*<<< orphan*/  has_aux (struct perf_event*) ; 
 struct ring_buffer* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __perf_event_output_stop(struct perf_event *event, void *data)
{
	struct perf_event *parent = event->parent;
	struct remote_output *ro = data;
	struct ring_buffer *rb = ro->rb;
	struct stop_event_data sd = {
		.event	= event,
	};

	if (!has_aux(event))
		return;

	if (!parent)
		parent = event;

	/*
	 * In case of inheritance, it will be the parent that links to the
	 * ring-buffer, but it will be the child that's actually using it.
	 *
	 * We are using event::rb to determine if the event should be stopped,
	 * however this may race with ring_buffer_attach() (through set_output),
	 * which will make us skip the event that actually needs to be stopped.
	 * So ring_buffer_attach() has to stop an aux event before re-assigning
	 * its rb pointer.
	 */
	if (rcu_dereference(parent->rb) == rb)
		ro->err = __perf_event_stop(&sd);
}