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
struct trace_iterator {int /*<<< orphan*/  iter_flags; } ;
struct trace_buffer {int dummy; } ;
struct trace_array {int trace_flags; struct trace_buffer trace_buffer; } ;
struct inode {struct trace_array* i_private; } ;
struct file {int f_mode; int f_flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_ERR (struct trace_iterator*) ; 
 int O_TRUNC ; 
 int PTR_ERR (struct trace_iterator*) ; 
 int RING_BUFFER_ALL_CPUS ; 
 int /*<<< orphan*/  TRACE_FILE_LAT_FMT ; 
 int TRACE_ITER_LATENCY_FMT ; 
 struct trace_iterator* __tracing_open (struct inode*,struct file*,int) ; 
 scalar_t__ trace_array_get (struct trace_array*) ; 
 int /*<<< orphan*/  trace_array_put (struct trace_array*) ; 
 int tracing_get_cpu (struct inode*) ; 
 int /*<<< orphan*/  tracing_reset (struct trace_buffer*,int) ; 
 int /*<<< orphan*/  tracing_reset_online_cpus (struct trace_buffer*) ; 

__attribute__((used)) static int tracing_open(struct inode *inode, struct file *file)
{
	struct trace_array *tr = inode->i_private;
	struct trace_iterator *iter;
	int ret = 0;

	if (trace_array_get(tr) < 0)
		return -ENODEV;

	/* If this file was open for write, then erase contents */
	if ((file->f_mode & FMODE_WRITE) && (file->f_flags & O_TRUNC)) {
		int cpu = tracing_get_cpu(inode);
		struct trace_buffer *trace_buf = &tr->trace_buffer;

#ifdef CONFIG_TRACER_MAX_TRACE
		if (tr->current_trace->print_max)
			trace_buf = &tr->max_buffer;
#endif

		if (cpu == RING_BUFFER_ALL_CPUS)
			tracing_reset_online_cpus(trace_buf);
		else
			tracing_reset(trace_buf, cpu);
	}

	if (file->f_mode & FMODE_READ) {
		iter = __tracing_open(inode, file, false);
		if (IS_ERR(iter))
			ret = PTR_ERR(iter);
		else if (tr->trace_flags & TRACE_ITER_LATENCY_FMT)
			iter->iter_flags |= TRACE_FILE_LAT_FMT;
	}

	if (ret < 0)
		trace_array_put(tr);

	return ret;
}