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
struct trace_iterator {int dummy; } ;
struct ftrace_buffer_info {struct trace_iterator iter; } ;
struct file {struct ftrace_buffer_info* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  trace_poll (struct trace_iterator*,struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t
tracing_buffers_poll(struct file *filp, poll_table *poll_table)
{
	struct ftrace_buffer_info *info = filp->private_data;
	struct trace_iterator *iter = &info->iter;

	return trace_poll(iter, filp, poll_table);
}