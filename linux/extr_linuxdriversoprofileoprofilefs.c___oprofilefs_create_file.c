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
struct inode {void* i_private; struct file_operations const* i_fop; } ;
struct file_operations {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFREG ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,char const*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct inode* oprofilefs_get_inode (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __oprofilefs_create_file(struct dentry *root, char const *name,
	const struct file_operations *fops, int perm, void *priv)
{
	struct dentry *dentry;
	struct inode *inode;

	if (!root)
		return -ENOMEM;

	inode_lock(d_inode(root));
	dentry = d_alloc_name(root, name);
	if (!dentry) {
		inode_unlock(d_inode(root));
		return -ENOMEM;
	}
	inode = oprofilefs_get_inode(root->d_sb, S_IFREG | perm);
	if (!inode) {
		dput(dentry);
		inode_unlock(d_inode(root));
		return -ENOMEM;
	}
	inode->i_fop = fops;
	inode->i_private = priv;
	d_add(dentry, inode);
	inode_unlock(d_inode(root));
	return 0;
}