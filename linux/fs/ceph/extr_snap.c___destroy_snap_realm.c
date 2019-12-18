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
struct ceph_snap_realm {int /*<<< orphan*/  cached_context; struct ceph_snap_realm* snaps; struct ceph_snap_realm* prior_parent_snaps; scalar_t__ parent; int /*<<< orphan*/  child_item; int /*<<< orphan*/  node; int /*<<< orphan*/  ino; } ;
struct ceph_mds_client {int /*<<< orphan*/  num_snap_realms; int /*<<< orphan*/  snap_realms; } ;

/* Variables and functions */
 int /*<<< orphan*/  __put_snap_realm (struct ceph_mds_client*,scalar_t__) ; 
 int /*<<< orphan*/  ceph_put_snap_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_snap_realm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ceph_snap_realm*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __destroy_snap_realm(struct ceph_mds_client *mdsc,
				 struct ceph_snap_realm *realm)
{
	dout("__destroy_snap_realm %p %llx\n", realm, realm->ino);

	rb_erase(&realm->node, &mdsc->snap_realms);
	mdsc->num_snap_realms--;

	if (realm->parent) {
		list_del_init(&realm->child_item);
		__put_snap_realm(mdsc, realm->parent);
	}

	kfree(realm->prior_parent_snaps);
	kfree(realm->snaps);
	ceph_put_snap_context(realm->cached_context);
	kfree(realm);
}