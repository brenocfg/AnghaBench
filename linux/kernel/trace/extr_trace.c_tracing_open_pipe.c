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
struct trace_iterator {TYPE_1__* trace; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cpu_file; int /*<<< orphan*/ * trace_buffer; struct trace_array* tr; int /*<<< orphan*/  iter_flags; int /*<<< orphan*/  started; int /*<<< orphan*/  seq; } ;
struct trace_array {int trace_flags; size_t clock_id; TYPE_1__* current_trace; int /*<<< orphan*/  trace_buffer; } ;
struct inode {struct trace_array* i_private; } ;
struct file {struct trace_iterator* private_data; } ;
struct TYPE_4__ {scalar_t__ in_ns; } ;
struct TYPE_3__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  (* pipe_open ) (struct trace_iterator*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TRACE_FILE_LAT_FMT ; 
 int /*<<< orphan*/  TRACE_FILE_TIME_IN_NS ; 
 int TRACE_ITER_LATENCY_FMT ; 
 int /*<<< orphan*/  __trace_array_put (struct trace_array*) ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_setall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct trace_iterator*) ; 
 struct trace_iterator* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  stub1 (struct trace_iterator*) ; 
 TYPE_2__* trace_clocks ; 
 int /*<<< orphan*/  trace_seq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_types_lock ; 
 int tracing_check_open_get_tr (struct trace_array*) ; 
 int /*<<< orphan*/  tracing_get_cpu (struct inode*) ; 

__attribute__((used)) static int tracing_open_pipe(struct inode *inode, struct file *filp)
{
	struct trace_array *tr = inode->i_private;
	struct trace_iterator *iter;
	int ret;

	ret = tracing_check_open_get_tr(tr);
	if (ret)
		return ret;

	mutex_lock(&trace_types_lock);

	/* create a buffer to store the information to pass to userspace */
	iter = kzalloc(sizeof(*iter), GFP_KERNEL);
	if (!iter) {
		ret = -ENOMEM;
		__trace_array_put(tr);
		goto out;
	}

	trace_seq_init(&iter->seq);
	iter->trace = tr->current_trace;

	if (!alloc_cpumask_var(&iter->started, GFP_KERNEL)) {
		ret = -ENOMEM;
		goto fail;
	}

	/* trace pipe does not show start of buffer */
	cpumask_setall(iter->started);

	if (tr->trace_flags & TRACE_ITER_LATENCY_FMT)
		iter->iter_flags |= TRACE_FILE_LAT_FMT;

	/* Output in nanoseconds only if we are using a clock in nanoseconds. */
	if (trace_clocks[tr->clock_id].in_ns)
		iter->iter_flags |= TRACE_FILE_TIME_IN_NS;

	iter->tr = tr;
	iter->trace_buffer = &tr->trace_buffer;
	iter->cpu_file = tracing_get_cpu(inode);
	mutex_init(&iter->mutex);
	filp->private_data = iter;

	if (iter->trace->pipe_open)
		iter->trace->pipe_open(iter);

	nonseekable_open(inode, filp);

	tr->current_trace->ref++;
out:
	mutex_unlock(&trace_types_lock);
	return ret;

fail:
	kfree(iter);
	__trace_array_put(tr);
	mutex_unlock(&trace_types_lock);
	return ret;
}