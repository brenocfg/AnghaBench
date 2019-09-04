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
struct trace_iterator {int /*<<< orphan*/  mutex; int /*<<< orphan*/  started; TYPE_2__* trace; } ;
struct trace_array {TYPE_1__* current_trace; } ;
struct inode {struct trace_array* i_private; } ;
struct file {struct trace_iterator* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* pipe_close ) (struct trace_iterator*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct trace_iterator*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct trace_iterator*) ; 
 int /*<<< orphan*/  trace_array_put (struct trace_array*) ; 
 int /*<<< orphan*/  trace_types_lock ; 

__attribute__((used)) static int tracing_release_pipe(struct inode *inode, struct file *file)
{
	struct trace_iterator *iter = file->private_data;
	struct trace_array *tr = inode->i_private;

	mutex_lock(&trace_types_lock);

	tr->current_trace->ref--;

	if (iter->trace->pipe_close)
		iter->trace->pipe_close(iter);

	mutex_unlock(&trace_types_lock);

	free_cpumask_var(iter->started);
	mutex_destroy(&iter->mutex);
	kfree(iter);

	trace_array_put(tr);

	return 0;
}