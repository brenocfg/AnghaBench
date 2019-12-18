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
typedef  int u64 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ceph_snap_realm {int inode; struct ceph_snap_realm* parent; int /*<<< orphan*/  inodes_with_caps_lock; } ;
struct ceph_mds_client {int /*<<< orphan*/  snap_rwsem; } ;
struct ceph_inode_info {int i_max_files; int i_rfiles; int i_rsubdirs; int i_max_bytes; int i_rbytes; int /*<<< orphan*/  i_ceph_lock; struct ceph_snap_realm* i_snap_realm; } ;
typedef  int loff_t ;
typedef  enum quota_check_op { ____Placeholder_quota_check_op } quota_check_op ;
struct TYPE_2__ {struct ceph_mds_client* mdsc; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 scalar_t__ IS_ERR_OR_NULL (struct inode*) ; 
#define  QUOTA_CHECK_MAX_BYTES_APPROACHING_OP 130 
#define  QUOTA_CHECK_MAX_BYTES_OP 129 
#define  QUOTA_CHECK_MAX_FILES_OP 128 
 int /*<<< orphan*/  ceph_async_iput (struct inode*) ; 
 int /*<<< orphan*/  ceph_get_snap_realm (struct ceph_mds_client*,struct ceph_snap_realm*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 TYPE_1__* ceph_inode_to_client (struct inode*) ; 
 int /*<<< orphan*/  ceph_put_snap_realm (struct ceph_mds_client*,struct ceph_snap_realm*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  ceph_vinop (struct inode*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct inode* igrab (int) ; 
 struct inode* lookup_quotarealm_inode (struct ceph_mds_client*,int /*<<< orphan*/ ,struct ceph_snap_realm*) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool check_quota_exceeded(struct inode *inode, enum quota_check_op op,
				 loff_t delta)
{
	struct ceph_mds_client *mdsc = ceph_inode_to_client(inode)->mdsc;
	struct ceph_inode_info *ci;
	struct ceph_snap_realm *realm, *next;
	struct inode *in;
	u64 max, rvalue;
	bool exceeded = false;

	if (ceph_snap(inode) != CEPH_NOSNAP)
		return false;

	down_read(&mdsc->snap_rwsem);
restart:
	realm = ceph_inode(inode)->i_snap_realm;
	if (realm)
		ceph_get_snap_realm(mdsc, realm);
	else
		pr_err_ratelimited("check_quota_exceeded: ino (%llx.%llx) "
				   "null i_snap_realm\n", ceph_vinop(inode));
	while (realm) {
		bool has_inode;

		spin_lock(&realm->inodes_with_caps_lock);
		has_inode = realm->inode;
		in = has_inode ? igrab(realm->inode) : NULL;
		spin_unlock(&realm->inodes_with_caps_lock);
		if (has_inode && !in)
			break;
		if (!in) {
			up_read(&mdsc->snap_rwsem);
			in = lookup_quotarealm_inode(mdsc, inode->i_sb, realm);
			down_read(&mdsc->snap_rwsem);
			if (IS_ERR_OR_NULL(in))
				break;
			ceph_put_snap_realm(mdsc, realm);
			goto restart;
		}
		ci = ceph_inode(in);
		spin_lock(&ci->i_ceph_lock);
		if (op == QUOTA_CHECK_MAX_FILES_OP) {
			max = ci->i_max_files;
			rvalue = ci->i_rfiles + ci->i_rsubdirs;
		} else {
			max = ci->i_max_bytes;
			rvalue = ci->i_rbytes;
		}
		spin_unlock(&ci->i_ceph_lock);
		switch (op) {
		case QUOTA_CHECK_MAX_FILES_OP:
			exceeded = (max && (rvalue >= max));
			break;
		case QUOTA_CHECK_MAX_BYTES_OP:
			exceeded = (max && (rvalue + delta > max));
			break;
		case QUOTA_CHECK_MAX_BYTES_APPROACHING_OP:
			if (max) {
				if (rvalue >= max)
					exceeded = true;
				else {
					/*
					 * when we're writing more that 1/16th
					 * of the available space
					 */
					exceeded =
						(((max - rvalue) >> 4) < delta);
				}
			}
			break;
		default:
			/* Shouldn't happen */
			pr_warn("Invalid quota check op (%d)\n", op);
			exceeded = true; /* Just break the loop */
		}
		/* avoid calling iput_final() while holding mdsc->snap_rwsem */
		ceph_async_iput(in);

		next = realm->parent;
		if (exceeded || !next)
			break;
		ceph_get_snap_realm(mdsc, next);
		ceph_put_snap_realm(mdsc, realm);
		realm = next;
	}
	if (realm)
		ceph_put_snap_realm(mdsc, realm);
	up_read(&mdsc->snap_rwsem);

	return exceeded;
}