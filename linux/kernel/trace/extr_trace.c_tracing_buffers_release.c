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
struct trace_iterator {TYPE_1__* trace_buffer; TYPE_3__* tr; } ;
struct inode {int dummy; } ;
struct ftrace_buffer_info {scalar_t__ spare; int /*<<< orphan*/  spare_cpu; struct trace_iterator iter; } ;
struct file {struct ftrace_buffer_info* private_data; } ;
struct TYPE_6__ {TYPE_2__* current_trace; } ;
struct TYPE_5__ {int /*<<< orphan*/  ref; } ;
struct TYPE_4__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __trace_array_put (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct ftrace_buffer_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_buffer_free_read_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_types_lock ; 

__attribute__((used)) static int tracing_buffers_release(struct inode *inode, struct file *file)
{
	struct ftrace_buffer_info *info = file->private_data;
	struct trace_iterator *iter = &info->iter;

	mutex_lock(&trace_types_lock);

	iter->tr->current_trace->ref--;

	__trace_array_put(iter->tr);

	if (info->spare)
		ring_buffer_free_read_page(iter->trace_buffer->buffer,
					   info->spare_cpu, info->spare);
	kfree(info);

	mutex_unlock(&trace_types_lock);

	return 0;
}