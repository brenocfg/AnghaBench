#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ceph_mds_client {int /*<<< orphan*/  dentry_list_lock; } ;
struct ceph_dentry_info {int flags; int /*<<< orphan*/  lease_list; TYPE_1__* dentry; } ;
struct TYPE_4__ {struct ceph_mds_client* mdsc; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int CEPH_DENTRY_SHRINK_LIST ; 
 TYPE_2__* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __dentry_lease_unlist(struct ceph_dentry_info *di)
{
	struct ceph_mds_client *mdsc;
	if (di->flags & CEPH_DENTRY_SHRINK_LIST)
		return;
	if (list_empty(&di->lease_list))
		return;

	mdsc = ceph_sb_to_client(di->dentry->d_sb)->mdsc;
	spin_lock(&mdsc->dentry_list_lock);
	list_del_init(&di->lease_list);
	spin_unlock(&mdsc->dentry_list_lock);
}