#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int len; } ;
struct trace_seq {char* buffer; TYPE_3__ seq; } ;
struct trace_iterator {TYPE_1__* ent; int /*<<< orphan*/  cpu; struct fgraph_data* private; struct trace_array* tr; } ;
struct trace_event {TYPE_2__* funcs; } ;
struct trace_entry {int /*<<< orphan*/  type; } ;
struct trace_array {unsigned long trace_flags; } ;
struct fgraph_data {int /*<<< orphan*/  cpu_data; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;
struct TYPE_8__ {int depth; } ;
struct TYPE_6__ {int (* trace ) (struct trace_iterator*,unsigned long,struct trace_event*) ;} ;
struct TYPE_5__ {int type; } ;

/* Variables and functions */
 int FLAGS_FILL_FULL ; 
#define  TRACE_BPRINT 130 
#define  TRACE_BPUTS 129 
 int TRACE_GRAPH_INDENT ; 
 unsigned long TRACE_ITER_SYM_MASK ; 
#define  TRACE_PRINT 128 
 int TRACE_TYPE_HANDLED ; 
 int TRACE_TYPE_UNHANDLED ; 
 struct trace_event* ftrace_find_event (int /*<<< orphan*/ ) ; 
 TYPE_4__* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_graph_duration (struct trace_array*,int /*<<< orphan*/ ,struct trace_seq*,int) ; 
 int /*<<< orphan*/  print_graph_prologue (struct trace_iterator*,struct trace_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct trace_iterator*,unsigned long,struct trace_event*) ; 
 int trace_handle_return (struct trace_seq*) ; 
 int trace_print_bprintk_msg_only (struct trace_iterator*) ; 
 int trace_print_bputs_msg_only (struct trace_iterator*) ; 
 int trace_print_printk_msg_only (struct trace_iterator*) ; 
 scalar_t__ trace_seq_has_overflowed (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

__attribute__((used)) static enum print_line_t
print_graph_comment(struct trace_seq *s, struct trace_entry *ent,
		    struct trace_iterator *iter, u32 flags)
{
	struct trace_array *tr = iter->tr;
	unsigned long sym_flags = (tr->trace_flags & TRACE_ITER_SYM_MASK);
	struct fgraph_data *data = iter->private;
	struct trace_event *event;
	int depth = 0;
	int ret;
	int i;

	if (data)
		depth = per_cpu_ptr(data->cpu_data, iter->cpu)->depth;

	print_graph_prologue(iter, s, 0, 0, flags);

	/* No time */
	print_graph_duration(tr, 0, s, flags | FLAGS_FILL_FULL);

	/* Indentation */
	if (depth > 0)
		for (i = 0; i < (depth + 1) * TRACE_GRAPH_INDENT; i++)
			trace_seq_putc(s, ' ');

	/* The comment */
	trace_seq_puts(s, "/* ");

	switch (iter->ent->type) {
	case TRACE_BPUTS:
		ret = trace_print_bputs_msg_only(iter);
		if (ret != TRACE_TYPE_HANDLED)
			return ret;
		break;
	case TRACE_BPRINT:
		ret = trace_print_bprintk_msg_only(iter);
		if (ret != TRACE_TYPE_HANDLED)
			return ret;
		break;
	case TRACE_PRINT:
		ret = trace_print_printk_msg_only(iter);
		if (ret != TRACE_TYPE_HANDLED)
			return ret;
		break;
	default:
		event = ftrace_find_event(ent->type);
		if (!event)
			return TRACE_TYPE_UNHANDLED;

		ret = event->funcs->trace(iter, sym_flags, event);
		if (ret != TRACE_TYPE_HANDLED)
			return ret;
	}

	if (trace_seq_has_overflowed(s))
		goto out;

	/* Strip ending newline */
	if (s->buffer[s->seq.len - 1] == '\n') {
		s->buffer[s->seq.len - 1] = '\0';
		s->seq.len--;
	}

	trace_seq_puts(s, " */\n");
 out:
	return trace_handle_return(s);
}