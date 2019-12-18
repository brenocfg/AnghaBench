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
struct inode {int dummy; } ;
struct ceph_snap_realm {int dummy; } ;
struct ceph_mds_client {int /*<<< orphan*/  snap_rwsem; } ;
struct TYPE_2__ {struct ceph_mds_client* mdsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  PTR_ERR (struct ceph_snap_realm*) ; 
 TYPE_1__* ceph_inode_to_client (struct inode*) ; 
 int /*<<< orphan*/  ceph_put_snap_realm (struct ceph_mds_client*,struct ceph_snap_realm*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct ceph_snap_realm* get_quota_realm (struct ceph_mds_client*,struct inode*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

bool ceph_quota_is_same_realm(struct inode *old, struct inode *new)
{
	struct ceph_mds_client *mdsc = ceph_inode_to_client(old)->mdsc;
	struct ceph_snap_realm *old_realm, *new_realm;
	bool is_same;

restart:
	/*
	 * We need to lookup 2 quota realms atomically, i.e. with snap_rwsem.
	 * However, get_quota_realm may drop it temporarily.  By setting the
	 * 'retry' parameter to 'false', we'll get -EAGAIN if the rwsem was
	 * dropped and we can then restart the whole operation.
	 */
	down_read(&mdsc->snap_rwsem);
	old_realm = get_quota_realm(mdsc, old, true);
	new_realm = get_quota_realm(mdsc, new, false);
	if (PTR_ERR(new_realm) == -EAGAIN) {
		up_read(&mdsc->snap_rwsem);
		if (old_realm)
			ceph_put_snap_realm(mdsc, old_realm);
		goto restart;
	}
	is_same = (old_realm == new_realm);
	up_read(&mdsc->snap_rwsem);

	if (old_realm)
		ceph_put_snap_realm(mdsc, old_realm);
	if (new_realm)
		ceph_put_snap_realm(mdsc, new_realm);

	return is_same;
}