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
 int ENODEV ; 
 scalar_t__ trace_array_get (struct trace_array*) ; 
 scalar_t__ tracing_disabled ; 

__attribute__((used)) static int tracing_open_generic_tr(struct inode *inode, struct file *filp)
{
	struct trace_array *tr = inode->i_private;

	if (tracing_disabled)
		return -ENODEV;

	if (trace_array_get(tr) < 0)
		return -ENODEV;

	filp->private_data = inode->i_private;

	return 0;
}