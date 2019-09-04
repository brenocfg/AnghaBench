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
struct posix_acl {int dummy; } ;
struct inode {int dummy; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_CAP_XATTR_SHARED ; 
 scalar_t__ __ceph_caps_issued_mask (struct ceph_inode_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  forget_cached_acl (struct inode*,int) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ceph_set_cached_acl(struct inode *inode,
					int type, struct posix_acl *acl)
{
	struct ceph_inode_info *ci = ceph_inode(inode);

	spin_lock(&ci->i_ceph_lock);
	if (__ceph_caps_issued_mask(ci, CEPH_CAP_XATTR_SHARED, 0))
		set_cached_acl(inode, type, acl);
	else
		forget_cached_acl(inode, type);
	spin_unlock(&ci->i_ceph_lock);
}