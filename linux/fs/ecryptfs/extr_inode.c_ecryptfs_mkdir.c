#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 struct dentry* ecryptfs_dentry_to_lower (struct dentry*) ; 
 int ecryptfs_interpose (struct dentry*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsstack_copy_attr_times (struct inode*,TYPE_1__*) ; 
 int /*<<< orphan*/  fsstack_copy_inode_size (struct inode*,TYPE_1__*) ; 
 struct dentry* lock_parent (struct dentry*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_dir (struct dentry*) ; 
 int vfs_mkdir (TYPE_1__*,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecryptfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	int rc;
	struct dentry *lower_dentry;
	struct dentry *lower_dir_dentry;

	lower_dentry = ecryptfs_dentry_to_lower(dentry);
	lower_dir_dentry = lock_parent(lower_dentry);
	rc = vfs_mkdir(d_inode(lower_dir_dentry), lower_dentry, mode);
	if (rc || d_really_is_negative(lower_dentry))
		goto out;
	rc = ecryptfs_interpose(lower_dentry, dentry, dir->i_sb);
	if (rc)
		goto out;
	fsstack_copy_attr_times(dir, d_inode(lower_dir_dentry));
	fsstack_copy_inode_size(dir, d_inode(lower_dir_dentry));
	set_nlink(dir, d_inode(lower_dir_dentry)->i_nlink);
out:
	unlock_dir(lower_dir_dentry);
	if (d_really_is_negative(dentry))
		d_drop(dentry);
	return rc;
}