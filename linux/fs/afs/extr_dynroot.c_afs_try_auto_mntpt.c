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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  flags; TYPE_1__ fid; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int /*<<< orphan*/  AFS_VNODE_AUTOCELL ; 
 int ENOENT ; 
 struct inode* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  _enter (char*,struct dentry*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 struct inode* afs_iget_pseudo_dir (int /*<<< orphan*/ ,int) ; 
 int afs_probe_cell_name (struct dentry*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct inode *afs_try_auto_mntpt(struct dentry *dentry, struct inode *dir)
{
	struct afs_vnode *vnode = AFS_FS_I(dir);
	struct inode *inode;
	int ret = -ENOENT;

	_enter("%p{%pd}, {%llx:%llu}",
	       dentry, dentry, vnode->fid.vid, vnode->fid.vnode);

	if (!test_bit(AFS_VNODE_AUTOCELL, &vnode->flags))
		goto out;

	ret = afs_probe_cell_name(dentry);
	if (ret < 0)
		goto out;

	inode = afs_iget_pseudo_dir(dir->i_sb, false);
	if (IS_ERR(inode)) {
		ret = PTR_ERR(inode);
		goto out;
	}

	_leave("= %p", inode);
	return inode;

out:
	_leave("= %d", ret);
	return ret == -ENOENT ? NULL : ERR_PTR(ret);
}