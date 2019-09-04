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
struct ceph_snap_realm {int /*<<< orphan*/  empty_item; int /*<<< orphan*/  nref; int /*<<< orphan*/  ino; } ;
struct ceph_mds_client {int /*<<< orphan*/  snap_empty_lock; int /*<<< orphan*/  snap_empty; int /*<<< orphan*/  snap_rwsem; } ;

/* Variables and functions */
 int /*<<< orphan*/  __destroy_snap_realm (struct ceph_mds_client*,struct ceph_snap_realm*) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,struct ceph_snap_realm*,scalar_t__,scalar_t__) ; 
 scalar_t__ down_write_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void ceph_put_snap_realm(struct ceph_mds_client *mdsc,
			 struct ceph_snap_realm *realm)
{
	dout("put_snap_realm %llx %p %d -> %d\n", realm->ino, realm,
	     atomic_read(&realm->nref), atomic_read(&realm->nref)-1);
	if (!atomic_dec_and_test(&realm->nref))
		return;

	if (down_write_trylock(&mdsc->snap_rwsem)) {
		__destroy_snap_realm(mdsc, realm);
		up_write(&mdsc->snap_rwsem);
	} else {
		spin_lock(&mdsc->snap_empty_lock);
		list_add(&realm->empty_item, &mdsc->snap_empty);
		spin_unlock(&mdsc->snap_empty_lock);
	}
}