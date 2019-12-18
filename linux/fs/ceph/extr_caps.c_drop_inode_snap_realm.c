#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ceph_snap_realm {scalar_t__ ino; int /*<<< orphan*/  inodes_with_caps_lock; int /*<<< orphan*/ * inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {scalar_t__ ino; } ;
struct ceph_inode_info {TYPE_2__ vfs_inode; TYPE_1__ i_vino; struct ceph_snap_realm* i_snap_realm; int /*<<< orphan*/  i_snap_realm_counter; int /*<<< orphan*/  i_snap_realm_item; } ;
struct TYPE_6__ {int /*<<< orphan*/  mdsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_put_snap_realm (int /*<<< orphan*/ ,struct ceph_snap_realm*) ; 
 TYPE_3__* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drop_inode_snap_realm(struct ceph_inode_info *ci)
{
	struct ceph_snap_realm *realm = ci->i_snap_realm;
	spin_lock(&realm->inodes_with_caps_lock);
	list_del_init(&ci->i_snap_realm_item);
	ci->i_snap_realm_counter++;
	ci->i_snap_realm = NULL;
	if (realm->ino == ci->i_vino.ino)
		realm->inode = NULL;
	spin_unlock(&realm->inodes_with_caps_lock);
	ceph_put_snap_realm(ceph_sb_to_client(ci->vfs_inode.i_sb)->mdsc,
			    realm);
}