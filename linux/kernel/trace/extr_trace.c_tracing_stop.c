#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ring_buffer {int dummy; } ;
struct TYPE_5__ {struct ring_buffer* buffer; } ;
struct TYPE_4__ {struct ring_buffer* buffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  start_lock; int /*<<< orphan*/  max_lock; TYPE_2__ max_buffer; TYPE_1__ trace_buffer; int /*<<< orphan*/  stop_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__ global_trace ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ring_buffer_record_disable (struct ring_buffer*) ; 

void tracing_stop(void)
{
	struct ring_buffer *buffer;
	unsigned long flags;

	raw_spin_lock_irqsave(&global_trace.start_lock, flags);
	if (global_trace.stop_count++)
		goto out;

	/* Prevent the buffers from switching */
	arch_spin_lock(&global_trace.max_lock);

	buffer = global_trace.trace_buffer.buffer;
	if (buffer)
		ring_buffer_record_disable(buffer);

#ifdef CONFIG_TRACER_MAX_TRACE
	buffer = global_trace.max_buffer.buffer;
	if (buffer)
		ring_buffer_record_disable(buffer);
#endif

	arch_spin_unlock(&global_trace.max_lock);

 out:
	raw_spin_unlock_irqrestore(&global_trace.start_lock, flags);
}