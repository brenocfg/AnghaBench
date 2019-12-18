#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trace_array {TYPE_2__* current_trace; int /*<<< orphan*/  trace_buffer; } ;
struct inode {struct trace_array* i_private; } ;
struct TYPE_3__ {int /*<<< orphan*/ * trace_buffer; TYPE_2__* trace; int /*<<< orphan*/  cpu_file; struct trace_array* tr; } ;
struct ftrace_buffer_info {unsigned int read; int /*<<< orphan*/ * spare; TYPE_1__ iter; } ;
struct file {struct ftrace_buffer_info* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ftrace_buffer_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  trace_array_put (struct trace_array*) ; 
 int /*<<< orphan*/  trace_types_lock ; 
 int tracing_check_open_get_tr (struct trace_array*) ; 
 int /*<<< orphan*/  tracing_get_cpu (struct inode*) ; 

__attribute__((used)) static int tracing_buffers_open(struct inode *inode, struct file *filp)
{
	struct trace_array *tr = inode->i_private;
	struct ftrace_buffer_info *info;
	int ret;

	ret = tracing_check_open_get_tr(tr);
	if (ret)
		return ret;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info) {
		trace_array_put(tr);
		return -ENOMEM;
	}

	mutex_lock(&trace_types_lock);

	info->iter.tr		= tr;
	info->iter.cpu_file	= tracing_get_cpu(inode);
	info->iter.trace	= tr->current_trace;
	info->iter.trace_buffer = &tr->trace_buffer;
	info->spare		= NULL;
	/* Force reading ring buffer for first read */
	info->read		= (unsigned int)-1;

	filp->private_data = info;

	tr->current_trace->ref++;

	mutex_unlock(&trace_types_lock);

	ret = nonseekable_open(inode, filp);
	if (ret < 0)
		trace_array_put(tr);

	return ret;
}