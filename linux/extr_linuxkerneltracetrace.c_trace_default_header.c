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
struct trace_iterator {int iter_flags; int /*<<< orphan*/  trace_buffer; struct trace_array* tr; } ;
struct trace_array {unsigned long trace_flags; } ;
struct seq_file {struct trace_iterator* private; } ;

/* Variables and functions */
 int TRACE_FILE_LAT_FMT ; 
 unsigned long TRACE_ITER_CONTEXT_INFO ; 
 unsigned long TRACE_ITER_IRQ_INFO ; 
 unsigned long TRACE_ITER_VERBOSE ; 
 int /*<<< orphan*/  print_func_help_header (int /*<<< orphan*/ ,struct seq_file*,unsigned long) ; 
 int /*<<< orphan*/  print_func_help_header_irq (int /*<<< orphan*/ ,struct seq_file*,unsigned long) ; 
 int /*<<< orphan*/  print_lat_help_header (struct seq_file*) ; 
 int /*<<< orphan*/  print_trace_header (struct seq_file*,struct trace_iterator*) ; 
 scalar_t__ trace_empty (struct trace_iterator*) ; 

void trace_default_header(struct seq_file *m)
{
	struct trace_iterator *iter = m->private;
	struct trace_array *tr = iter->tr;
	unsigned long trace_flags = tr->trace_flags;

	if (!(trace_flags & TRACE_ITER_CONTEXT_INFO))
		return;

	if (iter->iter_flags & TRACE_FILE_LAT_FMT) {
		/* print nothing if the buffers are empty */
		if (trace_empty(iter))
			return;
		print_trace_header(m, iter);
		if (!(trace_flags & TRACE_ITER_VERBOSE))
			print_lat_help_header(m);
	} else {
		if (!(trace_flags & TRACE_ITER_VERBOSE)) {
			if (trace_flags & TRACE_ITER_IRQ_INFO)
				print_func_help_header_irq(iter->trace_buffer,
							   m, trace_flags);
			else
				print_func_help_header(iter->trace_buffer, m,
						       trace_flags);
		}
	}
}