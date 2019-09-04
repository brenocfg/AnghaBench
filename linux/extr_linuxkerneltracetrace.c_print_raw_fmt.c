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
struct trace_seq {int dummy; } ;
struct trace_iterator {int /*<<< orphan*/  ts; int /*<<< orphan*/  cpu; struct trace_entry* ent; struct trace_seq seq; struct trace_array* tr; } ;
struct trace_event {TYPE_1__* funcs; } ;
struct trace_entry {int /*<<< orphan*/  type; int /*<<< orphan*/  pid; } ;
struct trace_array {int trace_flags; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;
struct TYPE_2__ {int (* raw ) (struct trace_iterator*,int /*<<< orphan*/ ,struct trace_event*) ;} ;

/* Variables and functions */
 int TRACE_ITER_CONTEXT_INFO ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 struct trace_event* ftrace_find_event (int /*<<< orphan*/ ) ; 
 int stub1 (struct trace_iterator*,int /*<<< orphan*/ ,struct trace_event*) ; 
 int trace_handle_return (struct trace_seq*) ; 
 scalar_t__ trace_seq_has_overflowed (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static enum print_line_t print_raw_fmt(struct trace_iterator *iter)
{
	struct trace_array *tr = iter->tr;
	struct trace_seq *s = &iter->seq;
	struct trace_entry *entry;
	struct trace_event *event;

	entry = iter->ent;

	if (tr->trace_flags & TRACE_ITER_CONTEXT_INFO)
		trace_seq_printf(s, "%d %d %llu ",
				 entry->pid, iter->cpu, iter->ts);

	if (trace_seq_has_overflowed(s))
		return TRACE_TYPE_PARTIAL_LINE;

	event = ftrace_find_event(entry->type);
	if (event)
		return event->funcs->raw(iter, 0, event);

	trace_seq_printf(s, "%d ?\n", entry->type);

	return trace_handle_return(s);
}