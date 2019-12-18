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
struct TYPE_2__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * buffer; } ;
struct trace_array {int allocated_snapshot; TYPE_1__ trace_buffer; TYPE_1__ max_buffer; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ WARN_ON (int) ; 
 int allocate_snapshot ; 
 int allocate_trace_buffer (struct trace_array*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_buffer_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int allocate_trace_buffers(struct trace_array *tr, int size)
{
	int ret;

	ret = allocate_trace_buffer(tr, &tr->trace_buffer, size);
	if (ret)
		return ret;

#ifdef CONFIG_TRACER_MAX_TRACE
	ret = allocate_trace_buffer(tr, &tr->max_buffer,
				    allocate_snapshot ? size : 1);
	if (WARN_ON(ret)) {
		ring_buffer_free(tr->trace_buffer.buffer);
		tr->trace_buffer.buffer = NULL;
		free_percpu(tr->trace_buffer.data);
		tr->trace_buffer.data = NULL;
		return -ENOMEM;
	}
	tr->allocated_snapshot = allocate_snapshot;

	/*
	 * Only the top level trace array gets its snapshot allocated
	 * from the kernel command line.
	 */
	allocate_snapshot = false;
#endif
	return 0;
}