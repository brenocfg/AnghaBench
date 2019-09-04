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
struct ceph_snap_realm {struct ceph_snap_realm* parent; int /*<<< orphan*/  inodes_with_caps_lock; scalar_t__ inode; } ;
struct ceph_mds_client {int dummy; } ;
struct ceph_inode_info {struct ceph_snap_realm* i_snap_realm; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 int __ceph_has_any_quota (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  ceph_get_snap_realm (struct ceph_mds_client*,struct ceph_snap_realm*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  ceph_put_snap_realm (struct ceph_mds_client*,struct ceph_snap_realm*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  ceph_vinop (struct inode*) ; 
 struct inode* igrab (scalar_t__) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ceph_snap_realm *get_quota_realm(struct ceph_mds_client *mdsc,
					       struct inode *inode)
{
	struct ceph_inode_info *ci = NULL;
	struct ceph_snap_realm *realm, *next;
	struct inode *in;
	bool has_quota;

	if (ceph_snap(inode) != CEPH_NOSNAP)
		return NULL;

	realm = ceph_inode(inode)->i_snap_realm;
	if (realm)
		ceph_get_snap_realm(mdsc, realm);
	else
		pr_err_ratelimited("get_quota_realm: ino (%llx.%llx) "
				   "null i_snap_realm\n", ceph_vinop(inode));
	while (realm) {
		spin_lock(&realm->inodes_with_caps_lock);
		in = realm->inode ? igrab(realm->inode) : NULL;
		spin_unlock(&realm->inodes_with_caps_lock);
		if (!in)
			break;

		ci = ceph_inode(in);
		has_quota = __ceph_has_any_quota(ci);
		iput(in);

		next = realm->parent;
		if (has_quota || !next)
		       return realm;

		ceph_get_snap_realm(mdsc, next);
		ceph_put_snap_realm(mdsc, realm);
		realm = next;
	}
	if (realm)
		ceph_put_snap_realm(mdsc, realm);

	return NULL;
}