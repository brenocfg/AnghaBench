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
struct inode {struct trace_array* i_private; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int /*<<< orphan*/  seq_release (struct inode*,struct file*) ; 
 int /*<<< orphan*/  trace_array_put (struct trace_array*) ; 

__attribute__((used)) static int tracing_err_log_release(struct inode *inode, struct file *file)
{
	struct trace_array *tr = inode->i_private;

	trace_array_put(tr);

	if (file->f_mode & FMODE_READ)
		seq_release(inode, file);

	return 0;
}