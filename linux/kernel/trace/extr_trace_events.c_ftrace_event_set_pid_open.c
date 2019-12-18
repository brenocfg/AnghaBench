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
struct seq_operations {int dummy; } ;
struct inode {struct trace_array* i_private; } ;
struct file {int f_mode; int f_flags; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  ftrace_clear_event_pids (struct trace_array*) ; 
 int ftrace_event_open (struct inode*,struct file*,struct seq_operations const*) ; 
 struct seq_operations show_set_pid_seq_ops ; 
 int /*<<< orphan*/  trace_array_put (struct trace_array*) ; 
 int tracing_check_open_get_tr (struct trace_array*) ; 

__attribute__((used)) static int
ftrace_event_set_pid_open(struct inode *inode, struct file *file)
{
	const struct seq_operations *seq_ops = &show_set_pid_seq_ops;
	struct trace_array *tr = inode->i_private;
	int ret;

	ret = tracing_check_open_get_tr(tr);
	if (ret)
		return ret;

	if ((file->f_mode & FMODE_WRITE) &&
	    (file->f_flags & O_TRUNC))
		ftrace_clear_event_pids(tr);

	ret = ftrace_event_open(inode, file, seq_ops);
	if (ret < 0)
		trace_array_put(tr);
	return ret;
}