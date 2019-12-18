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
struct seq_file {struct trace_array* private; } ;
struct inode {struct trace_array* i_private; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_traces_seq_ops ; 
 int /*<<< orphan*/  trace_array_put (struct trace_array*) ; 
 int tracing_check_open_get_tr (struct trace_array*) ; 

__attribute__((used)) static int show_traces_open(struct inode *inode, struct file *file)
{
	struct trace_array *tr = inode->i_private;
	struct seq_file *m;
	int ret;

	ret = tracing_check_open_get_tr(tr);
	if (ret)
		return ret;

	ret = seq_open(file, &show_traces_seq_ops);
	if (ret) {
		trace_array_put(tr);
		return ret;
	}

	m = file->private_data;
	m->private = tr;

	return 0;
}