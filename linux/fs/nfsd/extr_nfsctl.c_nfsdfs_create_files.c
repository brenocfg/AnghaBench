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
struct tree_descr {int mode; int /*<<< orphan*/  ops; scalar_t__* name; } ;
struct inode {int /*<<< orphan*/  i_private; int /*<<< orphan*/  i_fop; int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFREG ; 
 int /*<<< orphan*/  __get_nfsdfs_client (struct inode*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,scalar_t__*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_create (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 struct inode* nfsd_get_inode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsdfs_remove_files (struct dentry*) ; 

__attribute__((used)) static  int nfsdfs_create_files(struct dentry *root,
					const struct tree_descr *files)
{
	struct inode *dir = d_inode(root);
	struct inode *inode;
	struct dentry *dentry;
	int i;

	inode_lock(dir);
	for (i = 0; files->name && files->name[0]; i++, files++) {
		if (!files->name)
			continue;
		dentry = d_alloc_name(root, files->name);
		if (!dentry)
			goto out;
		inode = nfsd_get_inode(d_inode(root)->i_sb,
					S_IFREG | files->mode);
		if (!inode) {
			dput(dentry);
			goto out;
		}
		inode->i_fop = files->ops;
		inode->i_private = __get_nfsdfs_client(dir);
		d_add(dentry, inode);
		fsnotify_create(dir, dentry);
	}
	inode_unlock(dir);
	return 0;
out:
	nfsdfs_remove_files(root);
	inode_unlock(dir);
	return -ENOMEM;
}