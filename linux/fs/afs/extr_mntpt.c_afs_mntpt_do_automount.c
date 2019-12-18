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
struct vfsmount {int dummy; } ;
struct fs_context {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct vfsmount* ERR_CAST (struct fs_context*) ; 
 struct vfsmount* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct fs_context*) ; 
 int /*<<< orphan*/  afs_fs_type ; 
 int afs_mntpt_set_params (struct fs_context*,struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct vfsmount* fc_mount (struct fs_context*) ; 
 struct fs_context* fs_context_for_submount (int /*<<< orphan*/ *,struct dentry*) ; 
 int /*<<< orphan*/  put_fs_context (struct fs_context*) ; 

__attribute__((used)) static struct vfsmount *afs_mntpt_do_automount(struct dentry *mntpt)
{
	struct fs_context *fc;
	struct vfsmount *mnt;
	int ret;

	BUG_ON(!d_inode(mntpt));

	fc = fs_context_for_submount(&afs_fs_type, mntpt);
	if (IS_ERR(fc))
		return ERR_CAST(fc);

	ret = afs_mntpt_set_params(fc, mntpt);
	if (!ret)
		mnt = fc_mount(fc);
	else
		mnt = ERR_PTR(ret);

	put_fs_context(fc);
	return mnt;
}