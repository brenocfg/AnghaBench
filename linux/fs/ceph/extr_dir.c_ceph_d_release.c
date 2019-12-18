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
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/ * d_fsdata; } ;
struct ceph_dentry_info {scalar_t__ lease_session; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dentry_lease_unlist (struct ceph_dentry_info*) ; 
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 
 int /*<<< orphan*/  ceph_dentry_cachep ; 
 int /*<<< orphan*/  ceph_put_mds_session (scalar_t__) ; 
 int /*<<< orphan*/  dout (char*,struct dentry*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ceph_dentry_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ceph_d_release(struct dentry *dentry)
{
	struct ceph_dentry_info *di = ceph_dentry(dentry);

	dout("d_release %p\n", dentry);

	spin_lock(&dentry->d_lock);
	__dentry_lease_unlist(di);
	dentry->d_fsdata = NULL;
	spin_unlock(&dentry->d_lock);

	if (di->lease_session)
		ceph_put_mds_session(di->lease_session);
	kmem_cache_free(ceph_dentry_cachep, di);
}