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
struct inode {int i_opflags; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECRYPTFS_XATTR_NAME ; 
 int EOPNOTSUPP ; 
 int IOP_XATTR ; 
 int __vfs_setxattr (struct dentry*,struct inode*,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 struct dentry* ecryptfs_dentry_to_lower (struct dentry*) ; 
 int /*<<< orphan*/  fsstack_copy_attr_all (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static int
ecryptfs_write_metadata_to_xattr(struct dentry *ecryptfs_dentry,
				 struct inode *ecryptfs_inode,
				 char *page_virt, size_t size)
{
	int rc;
	struct dentry *lower_dentry = ecryptfs_dentry_to_lower(ecryptfs_dentry);
	struct inode *lower_inode = d_inode(lower_dentry);

	if (!(lower_inode->i_opflags & IOP_XATTR)) {
		rc = -EOPNOTSUPP;
		goto out;
	}

	inode_lock(lower_inode);
	rc = __vfs_setxattr(lower_dentry, lower_inode, ECRYPTFS_XATTR_NAME,
			    page_virt, size, 0);
	if (!rc && ecryptfs_inode)
		fsstack_copy_attr_all(ecryptfs_inode, lower_inode);
	inode_unlock(lower_inode);
out:
	return rc;
}