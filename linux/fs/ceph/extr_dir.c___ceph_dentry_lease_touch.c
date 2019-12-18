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
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct ceph_mds_client {int /*<<< orphan*/  dentry_list_lock; int /*<<< orphan*/  dentry_leases; } ;
struct ceph_dentry_info {int flags; int /*<<< orphan*/  lease_list; struct dentry* dentry; } ;
struct TYPE_2__ {struct ceph_mds_client* mdsc; } ;

/* Variables and functions */
 int CEPH_DENTRY_LEASE_LIST ; 
 int CEPH_DENTRY_REFERENCED ; 
 int CEPH_DENTRY_SHRINK_LIST ; 
 TYPE_1__* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_dentry_info*,struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __ceph_dentry_lease_touch(struct ceph_dentry_info *di)
{
	struct dentry *dn = di->dentry;
	struct ceph_mds_client *mdsc;

	dout("dentry_lease_touch %p %p '%pd'\n", di, dn, dn);

	di->flags |= CEPH_DENTRY_LEASE_LIST;
	if (di->flags & CEPH_DENTRY_SHRINK_LIST) {
		di->flags |= CEPH_DENTRY_REFERENCED;
		return;
	}

	mdsc = ceph_sb_to_client(dn->d_sb)->mdsc;
	spin_lock(&mdsc->dentry_list_lock);
	list_move_tail(&di->lease_list, &mdsc->dentry_leases);
	spin_unlock(&mdsc->dentry_list_lock);
}