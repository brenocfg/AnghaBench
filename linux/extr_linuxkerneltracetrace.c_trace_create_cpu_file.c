#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {void* i_cdev; } ;

/* Variables and functions */
 TYPE_1__* d_inode (struct dentry*) ; 
 struct dentry* trace_create_file (char const*,int /*<<< orphan*/ ,struct dentry*,void*,struct file_operations const*) ; 

__attribute__((used)) static struct dentry *
trace_create_cpu_file(const char *name, umode_t mode, struct dentry *parent,
		      void *data, long cpu, const struct file_operations *fops)
{
	struct dentry *ret = trace_create_file(name, mode, parent, data, fops);

	if (ret) /* See tracing_get_cpu() */
		d_inode(ret)->i_cdev = (void *)(cpu + 1);
	return ret;
}