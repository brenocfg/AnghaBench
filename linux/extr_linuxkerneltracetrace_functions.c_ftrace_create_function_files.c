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
struct trace_array {int flags; int /*<<< orphan*/  ops; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int TRACE_ARRAY_FL_GLOBAL ; 
 int allocate_ftrace_ops (struct trace_array*) ; 
 int /*<<< orphan*/  ftrace_create_filter_files (int /*<<< orphan*/ ,struct dentry*) ; 

int ftrace_create_function_files(struct trace_array *tr,
				 struct dentry *parent)
{
	int ret;

	/*
	 * The top level array uses the "global_ops", and the files are
	 * created on boot up.
	 */
	if (tr->flags & TRACE_ARRAY_FL_GLOBAL)
		return 0;

	ret = allocate_ftrace_ops(tr);
	if (ret)
		return ret;

	ftrace_create_filter_files(tr->ops, parent);

	return 0;
}