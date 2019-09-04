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
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_lock; } ;

/* Variables and functions */
 int __ceph_get_cap_mds (struct ceph_inode_info*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ceph_get_cap_mds(struct inode *inode)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	int mds;
	spin_lock(&ci->i_ceph_lock);
	mds = __ceph_get_cap_mds(ceph_inode(inode));
	spin_unlock(&ci->i_ceph_lock);
	return mds;
}