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
struct inode {int dummy; } ;
struct dentry {struct dentry* d_parent; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 struct inode* d_inode_rcu (struct dentry*) ; 
 struct inode* igrab (struct inode*) ; 

__attribute__((used)) static struct inode *get_nonsnap_parent(struct dentry *dentry)
{
	struct inode *inode = NULL;

	while (dentry && !IS_ROOT(dentry)) {
		inode = d_inode_rcu(dentry);
		if (!inode || ceph_snap(inode) == CEPH_NOSNAP)
			break;
		dentry = dentry->d_parent;
	}
	if (inode)
		inode = igrab(inode);
	return inode;
}