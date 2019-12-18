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
struct dentry {int dummy; } ;
struct ceph_dentry_info {int /*<<< orphan*/ * lease_session; } ;

/* Variables and functions */
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 
 int /*<<< orphan*/  ceph_put_mds_session (int /*<<< orphan*/ *) ; 

void __ceph_mdsc_drop_dentry_lease(struct dentry *dentry)
{
	struct ceph_dentry_info *di = ceph_dentry(dentry);

	ceph_put_mds_session(di->lease_session);
	di->lease_session = NULL;
}