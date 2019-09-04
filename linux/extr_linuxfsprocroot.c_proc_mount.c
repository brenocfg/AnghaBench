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
struct pid_namespace {int /*<<< orphan*/  user_ns; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int SB_KERNMOUNT ; 
 int /*<<< orphan*/  current ; 
 struct dentry* mount_ns (struct file_system_type*,int,void*,struct pid_namespace*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fill_super ; 
 struct pid_namespace* task_active_pid_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *proc_mount(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *data)
{
	struct pid_namespace *ns;

	if (flags & SB_KERNMOUNT) {
		ns = data;
		data = NULL;
	} else {
		ns = task_active_pid_ns(current);
	}

	return mount_ns(fs_type, flags, data, ns, ns->user_ns, proc_fill_super);
}