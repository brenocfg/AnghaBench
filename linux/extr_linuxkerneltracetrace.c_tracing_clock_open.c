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
 int ENODEV ; 
 int single_open (struct file*,int /*<<< orphan*/ ,struct trace_array*) ; 
 scalar_t__ trace_array_get (struct trace_array*) ; 
 int /*<<< orphan*/  trace_array_put (struct trace_array*) ; 
 int /*<<< orphan*/  tracing_clock_show ; 
 scalar_t__ tracing_disabled ; 

__attribute__((used)) static int tracing_clock_open(struct inode *inode, struct file *file)
{
	struct trace_array *tr = inode->i_private;
	int ret;

	if (tracing_disabled)
		return -ENODEV;

	if (trace_array_get(tr))
		return -ENODEV;

	ret = single_open(file, tracing_clock_show, inode->i_private);
	if (ret < 0)
		trace_array_put(tr);

	return ret;
}