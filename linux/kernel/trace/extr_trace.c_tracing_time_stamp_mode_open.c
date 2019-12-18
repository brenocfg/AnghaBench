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
struct file {int dummy; } ;

/* Variables and functions */
 int single_open (struct file*,int /*<<< orphan*/ ,struct trace_array*) ; 
 int /*<<< orphan*/  trace_array_put (struct trace_array*) ; 
 int tracing_check_open_get_tr (struct trace_array*) ; 
 int /*<<< orphan*/  tracing_time_stamp_mode_show ; 

__attribute__((used)) static int tracing_time_stamp_mode_open(struct inode *inode, struct file *file)
{
	struct trace_array *tr = inode->i_private;
	int ret;

	ret = tracing_check_open_get_tr(tr);
	if (ret)
		return ret;

	ret = single_open(file, tracing_time_stamp_mode_show, inode->i_private);
	if (ret < 0)
		trace_array_put(tr);

	return ret;
}