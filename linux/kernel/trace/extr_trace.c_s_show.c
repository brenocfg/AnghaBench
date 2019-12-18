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
struct trace_iterator {int leftover; int /*<<< orphan*/  seq; TYPE_1__* trace; scalar_t__ snapshot; scalar_t__ tr; int /*<<< orphan*/ * ent; } ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* print_header ) (struct seq_file*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_snapshot_help (struct seq_file*,struct trace_iterator*) ; 
 int /*<<< orphan*/  print_trace_line (struct trace_iterator*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  stub1 (struct seq_file*) ; 
 int /*<<< orphan*/  test_ftrace_alive (struct seq_file*) ; 
 int /*<<< orphan*/  trace_default_header (struct seq_file*) ; 
 scalar_t__ trace_empty (struct trace_iterator*) ; 
 int trace_print_seq (struct seq_file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s_show(struct seq_file *m, void *v)
{
	struct trace_iterator *iter = v;
	int ret;

	if (iter->ent == NULL) {
		if (iter->tr) {
			seq_printf(m, "# tracer: %s\n", iter->trace->name);
			seq_puts(m, "#\n");
			test_ftrace_alive(m);
		}
		if (iter->snapshot && trace_empty(iter))
			print_snapshot_help(m, iter);
		else if (iter->trace && iter->trace->print_header)
			iter->trace->print_header(m);
		else
			trace_default_header(m);

	} else if (iter->leftover) {
		/*
		 * If we filled the seq_file buffer earlier, we
		 * want to just show it now.
		 */
		ret = trace_print_seq(m, &iter->seq);

		/* ret should this time be zero, but you never know */
		iter->leftover = ret;

	} else {
		print_trace_line(iter);
		ret = trace_print_seq(m, &iter->seq);
		/*
		 * If we overflow the seq_file buffer, then it will
		 * ask us for this data again at start up.
		 * Use that instead.
		 *  ret is 0 if seq_file write succeeded.
		 *        -1 otherwise.
		 */
		iter->leftover = ret;
	}

	return 0;
}