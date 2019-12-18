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
struct trace_array {int /*<<< orphan*/  buffer_disabled; TYPE_1__ trace_buffer; } ;

/* Variables and functions */
 int ring_buffer_record_is_on (scalar_t__) ; 

bool tracer_tracing_is_on(struct trace_array *tr)
{
	if (tr->trace_buffer.buffer)
		return ring_buffer_record_is_on(tr->trace_buffer.buffer);
	return !tr->buffer_disabled;
}