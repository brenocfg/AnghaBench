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
 int __ceph_is_any_caps (struct ceph_inode_info*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ceph_is_any_caps(struct inode *inode)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	int ret;

	spin_lock(&ci->i_ceph_lock);
	ret = __ceph_is_any_caps(ci);
	spin_unlock(&ci->i_ceph_lock);

	return ret;
}