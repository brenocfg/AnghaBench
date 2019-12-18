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
struct trace_iterator {unsigned long long ts; TYPE_1__* trace_buffer; } ;
struct TYPE_2__ {unsigned long long time_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 int /*<<< orphan*/  do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,unsigned long long) ; 

__attribute__((used)) static void
print_graph_rel_time(struct trace_iterator *iter, struct trace_seq *s)
{
	unsigned long long usecs;

	usecs = iter->ts - iter->trace_buffer->time_start;
	do_div(usecs, NSEC_PER_USEC);

	trace_seq_printf(s, "%9llu us |  ", usecs);
}