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
struct ceph_mds_client {int /*<<< orphan*/  dentry_list_lock; } ;
struct ceph_dentry_info {int flags; int /*<<< orphan*/  lease_list; int /*<<< orphan*/  offset; struct dentry* dentry; } ;
typedef  struct ceph_mds_client* mdsc ;
typedef  struct ceph_dentry_info* di ;
struct TYPE_2__ {struct ceph_mds_client* mdsc; } ;

/* Variables and functions */
 int CEPH_DENTRY_LEASE_LIST ; 
 int CEPH_DENTRY_REFERENCED ; 
 int CEPH_DENTRY_SHRINK_LIST ; 
 int __dentry_dir_lease_touch (struct ceph_mds_client*,struct ceph_dentry_info*) ; 
 scalar_t__ __dentry_lease_is_valid (struct ceph_dentry_info*) ; 
 TYPE_1__* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_dentry_info*,struct dentry*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __ceph_dentry_dir_lease_touch(struct ceph_dentry_info *di)
{
	struct dentry *dn = di->dentry;
	struct ceph_mds_client *mdsc;

	dout("dentry_dir_lease_touch %p %p '%pd' (offset %lld)\n",
	     di, dn, dn, di->offset);

	if (!list_empty(&di->lease_list)) {
		if (di->flags & CEPH_DENTRY_LEASE_LIST) {
			/* don't remove dentry from dentry lease list
			 * if its lease is valid */
			if (__dentry_lease_is_valid(di))
				return;
		} else {
			di->flags |= CEPH_DENTRY_REFERENCED;
			return;
		}
	}

	if (di->flags & CEPH_DENTRY_SHRINK_LIST) {
		di->flags |= CEPH_DENTRY_REFERENCED;
		di->flags &= ~CEPH_DENTRY_LEASE_LIST;
		return;
	}

	mdsc = ceph_sb_to_client(dn->d_sb)->mdsc;
	spin_lock(&mdsc->dentry_list_lock);
	__dentry_dir_lease_touch(mdsc, di),
	spin_unlock(&mdsc->dentry_list_lock);
}