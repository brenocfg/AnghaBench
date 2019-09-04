#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipc_namespace {int /*<<< orphan*/  user_ns; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {TYPE_1__* nsproxy; } ;
struct TYPE_3__ {struct ipc_namespace* ipc_ns; } ;

/* Variables and functions */
 int SB_KERNMOUNT ; 
 TYPE_2__* current ; 
 struct dentry* mount_ns (struct file_system_type*,int,void*,struct ipc_namespace*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mqueue_fill_super ; 

__attribute__((used)) static struct dentry *mqueue_mount(struct file_system_type *fs_type,
			 int flags, const char *dev_name,
			 void *data)
{
	struct ipc_namespace *ns;
	if (flags & SB_KERNMOUNT) {
		ns = data;
		data = NULL;
	} else {
		ns = current->nsproxy->ipc_ns;
	}
	return mount_ns(fs_type, flags, data, ns, ns->user_ns, mqueue_fill_super);
}