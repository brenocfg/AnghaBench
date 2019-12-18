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
struct mount {TYPE_2__* mnt_parent; } ;
typedef  enum umount_tree_flags { ____Placeholder_umount_tree_flags } umount_tree_flags ;
struct TYPE_3__ {int mnt_flags; } ;
struct TYPE_4__ {TYPE_1__ mnt; } ;

/* Variables and functions */
 scalar_t__ IS_MNT_LOCKED (struct mount*) ; 
 int MNT_UMOUNT ; 
 int UMOUNT_CONNECTED ; 
 int UMOUNT_SYNC ; 
 int /*<<< orphan*/  mnt_has_parent (struct mount*) ; 

__attribute__((used)) static bool disconnect_mount(struct mount *mnt, enum umount_tree_flags how)
{
	/* Leaving mounts connected is only valid for lazy umounts */
	if (how & UMOUNT_SYNC)
		return true;

	/* A mount without a parent has nothing to be connected to */
	if (!mnt_has_parent(mnt))
		return true;

	/* Because the reference counting rules change when mounts are
	 * unmounted and connected, umounted mounts may not be
	 * connected to mounted mounts.
	 */
	if (!(mnt->mnt_parent->mnt.mnt_flags & MNT_UMOUNT))
		return true;

	/* Has it been requested that the mount remain connected? */
	if (how & UMOUNT_CONNECTED)
		return false;

	/* Is the mount locked such that it needs to remain connected? */
	if (IS_MNT_LOCKED(mnt))
		return false;

	/* By default disconnect the mount */
	return true;
}