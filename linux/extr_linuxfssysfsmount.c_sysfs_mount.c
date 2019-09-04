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
struct file_system_type {int dummy; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_iflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  KOBJ_NS_TYPE_NET ; 
 int /*<<< orphan*/  SB_I_USERNS_VISIBLE ; 
 int SB_KERNMOUNT ; 
 int /*<<< orphan*/  SYSFS_MAGIC ; 
 struct dentry* kernfs_mount_ns (struct file_system_type*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,void*) ; 
 int /*<<< orphan*/  kobj_ns_current_may_mount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_ns_drop (int /*<<< orphan*/ ,void*) ; 
 void* kobj_ns_grab_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_root ; 

__attribute__((used)) static struct dentry *sysfs_mount(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *data)
{
	struct dentry *root;
	void *ns;
	bool new_sb = false;

	if (!(flags & SB_KERNMOUNT)) {
		if (!kobj_ns_current_may_mount(KOBJ_NS_TYPE_NET))
			return ERR_PTR(-EPERM);
	}

	ns = kobj_ns_grab_current(KOBJ_NS_TYPE_NET);
	root = kernfs_mount_ns(fs_type, flags, sysfs_root,
				SYSFS_MAGIC, &new_sb, ns);
	if (!new_sb)
		kobj_ns_drop(KOBJ_NS_TYPE_NET, ns);
	else if (!IS_ERR(root))
		root->d_sb->s_iflags |= SB_I_USERNS_VISIBLE;

	return root;
}