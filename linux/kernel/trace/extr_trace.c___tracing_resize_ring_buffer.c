#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  buffer; } ;
struct trace_array {int flags; TYPE_2__ trace_buffer; TYPE_2__ max_buffer; TYPE_1__* current_trace; } ;
struct TYPE_8__ {unsigned long entries; } ;
struct TYPE_6__ {int /*<<< orphan*/  use_max_tr; } ;

/* Variables and functions */
 int RING_BUFFER_ALL_CPUS ; 
 int TRACE_ARRAY_FL_GLOBAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_5__* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int resize_buffer_duplicate_size (TYPE_2__*,TYPE_2__*,int) ; 
 int ring_buffer_expanded ; 
 int ring_buffer_resize (int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  set_buffer_entries (TYPE_2__*,unsigned long) ; 
 int tracing_disabled ; 

__attribute__((used)) static int __tracing_resize_ring_buffer(struct trace_array *tr,
					unsigned long size, int cpu)
{
	int ret;

	/*
	 * If kernel or user changes the size of the ring buffer
	 * we use the size that was given, and we can forget about
	 * expanding it later.
	 */
	ring_buffer_expanded = true;

	/* May be called before buffers are initialized */
	if (!tr->trace_buffer.buffer)
		return 0;

	ret = ring_buffer_resize(tr->trace_buffer.buffer, size, cpu);
	if (ret < 0)
		return ret;

#ifdef CONFIG_TRACER_MAX_TRACE
	if (!(tr->flags & TRACE_ARRAY_FL_GLOBAL) ||
	    !tr->current_trace->use_max_tr)
		goto out;

	ret = ring_buffer_resize(tr->max_buffer.buffer, size, cpu);
	if (ret < 0) {
		int r = resize_buffer_duplicate_size(&tr->trace_buffer,
						     &tr->trace_buffer, cpu);
		if (r < 0) {
			/*
			 * AARGH! We are left with different
			 * size max buffer!!!!
			 * The max buffer is our "snapshot" buffer.
			 * When a tracer needs a snapshot (one of the
			 * latency tracers), it swaps the max buffer
			 * with the saved snap shot. We succeeded to
			 * update the size of the main buffer, but failed to
			 * update the size of the max buffer. But when we tried
			 * to reset the main buffer to the original size, we
			 * failed there too. This is very unlikely to
			 * happen, but if it does, warn and kill all
			 * tracing.
			 */
			WARN_ON(1);
			tracing_disabled = 1;
		}
		return ret;
	}

	if (cpu == RING_BUFFER_ALL_CPUS)
		set_buffer_entries(&tr->max_buffer, size);
	else
		per_cpu_ptr(tr->max_buffer.data, cpu)->entries = size;

 out:
#endif /* CONFIG_TRACER_MAX_TRACE */

	if (cpu == RING_BUFFER_ALL_CPUS)
		set_buffer_entries(&tr->trace_buffer, size);
	else
		per_cpu_ptr(tr->trace_buffer.data, cpu)->entries = size;

	return ret;
}