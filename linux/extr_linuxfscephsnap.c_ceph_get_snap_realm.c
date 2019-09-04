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
struct ceph_snap_realm {int /*<<< orphan*/  empty_item; int /*<<< orphan*/  nref; } ;
struct ceph_mds_client {int /*<<< orphan*/  snap_empty_lock; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_snap_realm*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ceph_get_snap_realm(struct ceph_mds_client *mdsc,
			 struct ceph_snap_realm *realm)
{
	dout("get_realm %p %d -> %d\n", realm,
	     atomic_read(&realm->nref), atomic_read(&realm->nref)+1);
	/*
	 * since we _only_ increment realm refs or empty the empty
	 * list with snap_rwsem held, adjusting the empty list here is
	 * safe.  we do need to protect against concurrent empty list
	 * additions, however.
	 */
	if (atomic_inc_return(&realm->nref) == 1) {
		spin_lock(&mdsc->snap_empty_lock);
		list_del_init(&realm->empty_item);
		spin_unlock(&mdsc->snap_empty_lock);
	}
}