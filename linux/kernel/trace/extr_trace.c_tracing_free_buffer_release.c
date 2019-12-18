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
struct trace_array {int trace_flags; } ;
struct inode {struct trace_array* i_private; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_BUFFER_ALL_CPUS ; 
 int TRACE_ITER_STOP_ON_FREE ; 
 int /*<<< orphan*/  trace_array_put (struct trace_array*) ; 
 int /*<<< orphan*/  tracer_tracing_off (struct trace_array*) ; 
 int /*<<< orphan*/  tracing_resize_ring_buffer (struct trace_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tracing_free_buffer_release(struct inode *inode, struct file *filp)
{
	struct trace_array *tr = inode->i_private;

	/* disable tracing ? */
	if (tr->trace_flags & TRACE_ITER_STOP_ON_FREE)
		tracer_tracing_off(tr);
	/* resize the ring buffer to 0 */
	tracing_resize_ring_buffer(tr, 0, RING_BUFFER_ALL_CPUS);

	trace_array_put(tr);

	return 0;
}