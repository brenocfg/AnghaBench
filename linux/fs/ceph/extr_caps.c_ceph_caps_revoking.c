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
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_lock; struct inode vfs_inode; } ;

/* Variables and functions */
 int __ceph_caps_revoking_other (struct ceph_inode_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ceph_cap_string (int) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ceph_caps_revoking(struct ceph_inode_info *ci, int mask)
{
	struct inode *inode = &ci->vfs_inode;
	int ret;

	spin_lock(&ci->i_ceph_lock);
	ret = __ceph_caps_revoking_other(ci, NULL, mask);
	spin_unlock(&ci->i_ceph_lock);
	dout("ceph_caps_revoking %p %s = %d\n", inode,
	     ceph_cap_string(mask), ret);
	return ret;
}