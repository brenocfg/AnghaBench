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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct dentry {int /*<<< orphan*/  d_parent; int /*<<< orphan*/  d_sb; struct configfs_dirent* d_fsdata; } ;
struct configfs_dirent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct inode* configfs_new_inode (int /*<<< orphan*/ ,struct configfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configfs_set_inode_lock_class (struct configfs_dirent*,struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 

struct inode *configfs_create(struct dentry *dentry, umode_t mode)
{
	struct inode *inode = NULL;
	struct configfs_dirent *sd;
	struct inode *p_inode;

	if (!dentry)
		return ERR_PTR(-ENOENT);

	if (d_really_is_positive(dentry))
		return ERR_PTR(-EEXIST);

	sd = dentry->d_fsdata;
	inode = configfs_new_inode(mode, sd, dentry->d_sb);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	p_inode = d_inode(dentry->d_parent);
	p_inode->i_mtime = p_inode->i_ctime = current_time(p_inode);
	configfs_set_inode_lock_class(sd, inode);
	return inode;
}