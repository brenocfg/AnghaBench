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
struct TYPE_2__ {scalar_t__ buffer; } ;
struct trace_array {scalar_t__ buffer_disabled; TYPE_1__ trace_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ring_buffer_record_on (scalar_t__) ; 
 int /*<<< orphan*/  smp_wmb () ; 

void tracer_tracing_on(struct trace_array *tr)
{
	if (tr->trace_buffer.buffer)
		ring_buffer_record_on(tr->trace_buffer.buffer);
	/*
	 * This flag is looked at when buffers haven't been allocated
	 * yet, or by some tracers (like irqsoff), that just want to
	 * know if the ring buffer has been disabled, but it can handle
	 * races of where it gets disabled but we still do a record.
	 * As the check is in the fast path of the tracers, it is more
	 * important to be fast than accurate.
	 */
	tr->buffer_disabled = 0;
	/* Make the flag seen by readers */
	smp_wmb();
}