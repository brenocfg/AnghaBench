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
struct file {struct trace_array* private_data; } ;

/* Variables and functions */
 int tracing_check_open_get_tr (struct trace_array*) ; 

int tracing_open_generic_tr(struct inode *inode, struct file *filp)
{
	struct trace_array *tr = inode->i_private;
	int ret;

	ret = tracing_check_open_get_tr(tr);
	if (ret)
		return ret;

	filp->private_data = inode->i_private;

	return 0;
}