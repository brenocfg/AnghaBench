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
struct TYPE_2__ {struct ring_buffer* buffer; } ;
struct trace_array {int flags; int /*<<< orphan*/  start_lock; TYPE_1__ trace_buffer; int /*<<< orphan*/  stop_count; } ;
struct ring_buffer {int dummy; } ;

/* Variables and functions */
 int TRACE_ARRAY_FL_GLOBAL ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ring_buffer_record_disable (struct ring_buffer*) ; 
 void tracing_stop () ; 

__attribute__((used)) static void tracing_stop_tr(struct trace_array *tr)
{
	struct ring_buffer *buffer;
	unsigned long flags;

	/* If global, we need to also stop the max tracer */
	if (tr->flags & TRACE_ARRAY_FL_GLOBAL)
		return tracing_stop();

	raw_spin_lock_irqsave(&tr->start_lock, flags);
	if (tr->stop_count++)
		goto out;

	buffer = tr->trace_buffer.buffer;
	if (buffer)
		ring_buffer_record_disable(buffer);

 out:
	raw_spin_unlock_irqrestore(&tr->start_lock, flags);
}