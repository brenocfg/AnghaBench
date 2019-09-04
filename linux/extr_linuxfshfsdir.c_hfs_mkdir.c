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
typedef  int umode_t ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int hfs_cat_create (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  hfs_delete_inode (struct inode*) ; 
 struct inode* hfs_new_inode (struct inode*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

__attribute__((used)) static int hfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct inode *inode;
	int res;

	inode = hfs_new_inode(dir, &dentry->d_name, S_IFDIR | mode);
	if (!inode)
		return -ENOMEM;

	res = hfs_cat_create(inode->i_ino, dir, &dentry->d_name, inode);
	if (res) {
		clear_nlink(inode);
		hfs_delete_inode(inode);
		iput(inode);
		return res;
	}
	d_instantiate(dentry, inode);
	mark_inode_dirty(inode);
	return 0;
}