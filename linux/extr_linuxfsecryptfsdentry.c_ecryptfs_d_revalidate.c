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
struct inode {int /*<<< orphan*/  i_nlink; } ;
struct dentry {int d_flags; TYPE_1__* d_op; } ;
struct TYPE_2__ {int (* d_revalidate ) (struct dentry*,unsigned int) ;} ;

/* Variables and functions */
 int DCACHE_OP_REVALIDATE ; 
 int ECHILD ; 
 unsigned int LOOKUP_RCU ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 struct dentry* ecryptfs_dentry_to_lower (struct dentry*) ; 
 int /*<<< orphan*/  ecryptfs_inode_to_lower (struct inode*) ; 
 int /*<<< orphan*/  fsstack_copy_attr_all (struct inode*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dentry*,unsigned int) ; 

__attribute__((used)) static int ecryptfs_d_revalidate(struct dentry *dentry, unsigned int flags)
{
	struct dentry *lower_dentry = ecryptfs_dentry_to_lower(dentry);
	int rc = 1;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	if (lower_dentry->d_flags & DCACHE_OP_REVALIDATE)
		rc = lower_dentry->d_op->d_revalidate(lower_dentry, flags);

	if (d_really_is_positive(dentry)) {
		struct inode *inode = d_inode(dentry);

		fsstack_copy_attr_all(inode, ecryptfs_inode_to_lower(inode));
		if (!inode->i_nlink)
			return 0;
	}
	return rc;
}