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
struct trace_array {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftrace_pid_fops ; 
 int /*<<< orphan*/  trace_create_file (char*,int,struct dentry*,struct trace_array*,int /*<<< orphan*/ *) ; 

void ftrace_init_tracefs(struct trace_array *tr, struct dentry *d_tracer)
{
	trace_create_file("set_ftrace_pid", 0644, d_tracer,
			    tr, &ftrace_pid_fops);
}