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
typedef  int umode_t ;
struct inode {int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_fsdata; TYPE_1__ d_name; struct dentry* d_parent; } ;
struct configfs_fragment {int dummy; } ;
struct config_item {struct dentry* ci_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CONFIGFS_DIR ; 
 int CONFIGFS_USET_CREATING ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IRWXU ; 
 int S_IXUGO ; 
 struct inode* configfs_create (struct dentry*,int) ; 
 int /*<<< orphan*/  configfs_dir_inode_operations ; 
 int /*<<< orphan*/  configfs_dir_operations ; 
 int configfs_dirent_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int configfs_make_dirent (int /*<<< orphan*/ ,struct dentry*,struct config_item*,int,int,struct configfs_fragment*) ; 
 int /*<<< orphan*/  configfs_remove_dirent (struct dentry*) ; 
 int /*<<< orphan*/  configfs_set_dir_dirent_depth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int configfs_create_dir(struct config_item *item, struct dentry *dentry,
				struct configfs_fragment *frag)
{
	int error;
	umode_t mode = S_IFDIR| S_IRWXU | S_IRUGO | S_IXUGO;
	struct dentry *p = dentry->d_parent;
	struct inode *inode;

	BUG_ON(!item);

	error = configfs_dirent_exists(p->d_fsdata, dentry->d_name.name);
	if (unlikely(error))
		return error;

	error = configfs_make_dirent(p->d_fsdata, dentry, item, mode,
				     CONFIGFS_DIR | CONFIGFS_USET_CREATING,
				     frag);
	if (unlikely(error))
		return error;

	configfs_set_dir_dirent_depth(p->d_fsdata, dentry->d_fsdata);
	inode = configfs_create(dentry, mode);
	if (IS_ERR(inode))
		goto out_remove;

	inode->i_op = &configfs_dir_inode_operations;
	inode->i_fop = &configfs_dir_operations;
	/* directory inodes start off with i_nlink == 2 (for "." entry) */
	inc_nlink(inode);
	d_instantiate(dentry, inode);
	/* already hashed */
	dget(dentry);  /* pin directory dentries in core */
	inc_nlink(d_inode(p));
	item->ci_dentry = dentry;
	return 0;

out_remove:
	configfs_remove_dirent(dentry);
	return PTR_ERR(inode);
}