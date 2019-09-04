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
typedef  int u32 ;
struct trace_seq {int dummy; } ;
struct trace_array {int trace_flags; } ;

/* Variables and functions */
#define  FLAGS_FILL_END 130 
#define  FLAGS_FILL_FULL 129 
#define  FLAGS_FILL_START 128 
 int TRACE_GRAPH_PRINT_DURATION ; 
 int TRACE_GRAPH_PRINT_FILL_MASK ; 
 int TRACE_GRAPH_PRINT_OVERHEAD ; 
 int TRACE_ITER_CONTEXT_INFO ; 
 int /*<<< orphan*/  trace_find_mark (unsigned long long) ; 
 int /*<<< orphan*/  trace_print_graph_duration (unsigned long long,struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

__attribute__((used)) static void
print_graph_duration(struct trace_array *tr, unsigned long long duration,
		     struct trace_seq *s, u32 flags)
{
	if (!(flags & TRACE_GRAPH_PRINT_DURATION) ||
	    !(tr->trace_flags & TRACE_ITER_CONTEXT_INFO))
		return;

	/* No real adata, just filling the column with spaces */
	switch (flags & TRACE_GRAPH_PRINT_FILL_MASK) {
	case FLAGS_FILL_FULL:
		trace_seq_puts(s, "              |  ");
		return;
	case FLAGS_FILL_START:
		trace_seq_puts(s, "  ");
		return;
	case FLAGS_FILL_END:
		trace_seq_puts(s, " |");
		return;
	}

	/* Signal a overhead of time execution to the output */
	if (flags & TRACE_GRAPH_PRINT_OVERHEAD)
		trace_seq_printf(s, "%c ", trace_find_mark(duration));
	else
		trace_seq_puts(s, "  ");

	trace_print_graph_duration(duration, s);
	trace_seq_puts(s, "|  ");
}