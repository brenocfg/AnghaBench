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
struct vfsmount {TYPE_1__* mnt_sb; } ;
struct dentry {int d_flags; } ;
struct TYPE_2__ {struct dentry* s_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DCACHE_DISCONNECTED ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 scalar_t__ IS_ROOT (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  clear_disconnected (struct dentry*) ; 
 struct dentry* dget (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* reconnect_one (struct vfsmount*,struct dentry*,char*) ; 

__attribute__((used)) static int
reconnect_path(struct vfsmount *mnt, struct dentry *target_dir, char *nbuf)
{
	struct dentry *dentry, *parent;

	dentry = dget(target_dir);

	while (dentry->d_flags & DCACHE_DISCONNECTED) {
		BUG_ON(dentry == mnt->mnt_sb->s_root);

		if (IS_ROOT(dentry))
			parent = reconnect_one(mnt, dentry, nbuf);
		else
			parent = dget_parent(dentry);

		if (!parent)
			break;
		dput(dentry);
		if (IS_ERR(parent))
			return PTR_ERR(parent);
		dentry = parent;
	}
	dput(dentry);
	clear_disconnected(target_dir);
	return 0;
}