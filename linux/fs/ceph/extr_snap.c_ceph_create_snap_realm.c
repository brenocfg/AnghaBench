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
typedef  int /*<<< orphan*/  u64 ;
struct ceph_snap_realm {int /*<<< orphan*/  ino; int /*<<< orphan*/  inodes_with_caps_lock; int /*<<< orphan*/  inodes_with_caps; int /*<<< orphan*/  dirty_item; int /*<<< orphan*/  empty_item; int /*<<< orphan*/  child_item; int /*<<< orphan*/  children; int /*<<< orphan*/  nref; } ;
struct ceph_mds_client {int /*<<< orphan*/  num_snap_realms; int /*<<< orphan*/  snap_realms; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ceph_snap_realm* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __insert_snap_realm (int /*<<< orphan*/ *,struct ceph_snap_realm*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,struct ceph_snap_realm*) ; 
 struct ceph_snap_realm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ceph_snap_realm *ceph_create_snap_realm(
	struct ceph_mds_client *mdsc,
	u64 ino)
{
	struct ceph_snap_realm *realm;

	realm = kzalloc(sizeof(*realm), GFP_NOFS);
	if (!realm)
		return ERR_PTR(-ENOMEM);

	atomic_set(&realm->nref, 1);    /* for caller */
	realm->ino = ino;
	INIT_LIST_HEAD(&realm->children);
	INIT_LIST_HEAD(&realm->child_item);
	INIT_LIST_HEAD(&realm->empty_item);
	INIT_LIST_HEAD(&realm->dirty_item);
	INIT_LIST_HEAD(&realm->inodes_with_caps);
	spin_lock_init(&realm->inodes_with_caps_lock);
	__insert_snap_realm(&mdsc->snap_realms, realm);
	mdsc->num_snap_realms++;

	dout("create_snap_realm %llx %p\n", realm->ino, realm);
	return realm;
}