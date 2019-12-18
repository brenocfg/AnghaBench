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
struct ceph_mds_client {int /*<<< orphan*/  dentry_dir_leases; } ;
struct ceph_dentry_info {int flags; int /*<<< orphan*/  lease_list; int /*<<< orphan*/  time; scalar_t__ lease_gen; } ;

/* Variables and functions */
 int CEPH_DENTRY_LEASE_LIST ; 
 int CEPH_DENTRY_REFERENCED ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __dentry_dir_lease_touch(struct ceph_mds_client* mdsc,
				     struct ceph_dentry_info *di)
{
	di->flags &= ~(CEPH_DENTRY_LEASE_LIST | CEPH_DENTRY_REFERENCED);
	di->lease_gen = 0;
	di->time = jiffies;
	list_move_tail(&di->lease_list, &mdsc->dentry_dir_leases);
}