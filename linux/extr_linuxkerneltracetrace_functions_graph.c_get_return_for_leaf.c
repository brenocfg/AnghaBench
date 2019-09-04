#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct trace_iterator {int /*<<< orphan*/  cpu; TYPE_1__* trace_buffer; struct fgraph_data* private; } ;
struct ring_buffer_iter {int dummy; } ;
struct ring_buffer_event {int dummy; } ;
struct TYPE_10__ {scalar_t__ func; } ;
struct TYPE_8__ {scalar_t__ type; scalar_t__ pid; } ;
struct ftrace_graph_ret_entry {TYPE_5__ ret; TYPE_3__ ent; } ;
struct TYPE_9__ {scalar_t__ func; } ;
struct TYPE_7__ {scalar_t__ pid; } ;
struct ftrace_graph_ent_entry {TYPE_4__ graph_ent; TYPE_2__ ent; } ;
struct fgraph_data {struct ftrace_graph_ret_entry ret; struct ftrace_graph_ent_entry ent; scalar_t__ failed; } ;
struct TYPE_6__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 scalar_t__ TRACE_GRAPH_RET ; 
 int /*<<< orphan*/  ring_buffer_consume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ftrace_graph_ret_entry* ring_buffer_event_data (struct ring_buffer_event*) ; 
 struct ring_buffer_event* ring_buffer_iter_peek (struct ring_buffer_iter*,int /*<<< orphan*/ *) ; 
 struct ring_buffer_event* ring_buffer_peek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_buffer_read (struct ring_buffer_iter*,int /*<<< orphan*/ *) ; 
 struct ring_buffer_iter* trace_buffer_iter (struct trace_iterator*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ftrace_graph_ret_entry *
get_return_for_leaf(struct trace_iterator *iter,
		struct ftrace_graph_ent_entry *curr)
{
	struct fgraph_data *data = iter->private;
	struct ring_buffer_iter *ring_iter = NULL;
	struct ring_buffer_event *event;
	struct ftrace_graph_ret_entry *next;

	/*
	 * If the previous output failed to write to the seq buffer,
	 * then we just reuse the data from before.
	 */
	if (data && data->failed) {
		curr = &data->ent;
		next = &data->ret;
	} else {

		ring_iter = trace_buffer_iter(iter, iter->cpu);

		/* First peek to compare current entry and the next one */
		if (ring_iter)
			event = ring_buffer_iter_peek(ring_iter, NULL);
		else {
			/*
			 * We need to consume the current entry to see
			 * the next one.
			 */
			ring_buffer_consume(iter->trace_buffer->buffer, iter->cpu,
					    NULL, NULL);
			event = ring_buffer_peek(iter->trace_buffer->buffer, iter->cpu,
						 NULL, NULL);
		}

		if (!event)
			return NULL;

		next = ring_buffer_event_data(event);

		if (data) {
			/*
			 * Save current and next entries for later reference
			 * if the output fails.
			 */
			data->ent = *curr;
			/*
			 * If the next event is not a return type, then
			 * we only care about what type it is. Otherwise we can
			 * safely copy the entire event.
			 */
			if (next->ent.type == TRACE_GRAPH_RET)
				data->ret = *next;
			else
				data->ret.ent.type = next->ent.type;
		}
	}

	if (next->ent.type != TRACE_GRAPH_RET)
		return NULL;

	if (curr->ent.pid != next->ent.pid ||
			curr->graph_ent.func != next->ret.func)
		return NULL;

	/* this is a leaf, now advance the iterator */
	if (ring_iter)
		ring_buffer_read(ring_iter, NULL);

	return next;
}