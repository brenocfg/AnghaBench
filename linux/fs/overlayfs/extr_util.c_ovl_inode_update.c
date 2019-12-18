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
struct inode {struct inode* i_private; int /*<<< orphan*/  i_ino; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct dentry* __upperdentry; } ;

/* Variables and functions */
 TYPE_1__* OVL_I (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON (struct dentry*) ; 
 int /*<<< orphan*/  __insert_inode_hash (struct inode*,unsigned long) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ inode_unhashed (struct inode*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

void ovl_inode_update(struct inode *inode, struct dentry *upperdentry)
{
	struct inode *upperinode = d_inode(upperdentry);

	WARN_ON(OVL_I(inode)->__upperdentry);

	/*
	 * Make sure upperdentry is consistent before making it visible
	 */
	smp_wmb();
	OVL_I(inode)->__upperdentry = upperdentry;
	if (inode_unhashed(inode)) {
		if (!inode->i_ino)
			inode->i_ino = upperinode->i_ino;
		inode->i_private = upperinode;
		__insert_inode_hash(inode, (unsigned long) upperinode);
	}
}