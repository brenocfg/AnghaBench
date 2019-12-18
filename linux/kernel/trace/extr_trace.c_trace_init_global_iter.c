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
struct trace_iterator {int /*<<< orphan*/  iter_flags; TYPE_4__* tr; TYPE_2__* trace_buffer; TYPE_1__* trace; int /*<<< orphan*/  cpu_file; } ;
struct TYPE_6__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_8__ {size_t clock_id; TYPE_2__ trace_buffer; TYPE_1__* current_trace; } ;
struct TYPE_7__ {scalar_t__ in_ns; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* open ) (struct trace_iterator*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RING_BUFFER_ALL_CPUS ; 
 int /*<<< orphan*/  TRACE_FILE_ANNOTATE ; 
 int /*<<< orphan*/  TRACE_FILE_TIME_IN_NS ; 
 TYPE_4__ global_trace ; 
 scalar_t__ ring_buffer_overruns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct trace_iterator*) ; 
 TYPE_3__* trace_clocks ; 

void trace_init_global_iter(struct trace_iterator *iter)
{
	iter->tr = &global_trace;
	iter->trace = iter->tr->current_trace;
	iter->cpu_file = RING_BUFFER_ALL_CPUS;
	iter->trace_buffer = &global_trace.trace_buffer;

	if (iter->trace && iter->trace->open)
		iter->trace->open(iter);

	/* Annotate start of buffers if we had overruns */
	if (ring_buffer_overruns(iter->trace_buffer->buffer))
		iter->iter_flags |= TRACE_FILE_ANNOTATE;

	/* Output in nanoseconds only if we are using a clock in nanoseconds. */
	if (trace_clocks[iter->tr->clock_id].in_ns)
		iter->iter_flags |= TRACE_FILE_TIME_IN_NS;
}