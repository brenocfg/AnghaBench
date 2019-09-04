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
struct trace_seq {int /*<<< orphan*/  seq; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __trace_seq_init (struct trace_seq*) ; 
 int seq_buf_print_seq (struct seq_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_seq_init (struct trace_seq*) ; 

int trace_print_seq(struct seq_file *m, struct trace_seq *s)
{
	int ret;

	__trace_seq_init(s);

	ret = seq_buf_print_seq(m, &s->seq);

	/*
	 * Only reset this buffer if we successfully wrote to the
	 * seq_file buffer. This lets the caller try again or
	 * do something else with the contents.
	 */
	if (!ret)
		trace_seq_init(s);

	return ret;
}