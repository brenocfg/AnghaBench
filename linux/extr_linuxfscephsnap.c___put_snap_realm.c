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
struct ceph_snap_realm {int /*<<< orphan*/  nref; int /*<<< orphan*/  ino; } ;
struct ceph_mds_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __destroy_snap_realm (struct ceph_mds_client*,struct ceph_snap_realm*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,struct ceph_snap_realm*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void __put_snap_realm(struct ceph_mds_client *mdsc,
			     struct ceph_snap_realm *realm)
{
	dout("__put_snap_realm %llx %p %d -> %d\n", realm->ino, realm,
	     atomic_read(&realm->nref), atomic_read(&realm->nref)-1);
	if (atomic_dec_and_test(&realm->nref))
		__destroy_snap_realm(mdsc, realm);
}