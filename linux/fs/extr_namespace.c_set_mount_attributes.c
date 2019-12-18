#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int mnt_flags; } ;
struct mount {int /*<<< orphan*/  mnt_ns; TYPE_1__ mnt; } ;

/* Variables and functions */
 unsigned int MNT_USER_SETTABLE_MASK ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 int /*<<< orphan*/  touch_mnt_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 

__attribute__((used)) static void set_mount_attributes(struct mount *mnt, unsigned int mnt_flags)
{
	lock_mount_hash();
	mnt_flags |= mnt->mnt.mnt_flags & ~MNT_USER_SETTABLE_MASK;
	mnt->mnt.mnt_flags = mnt_flags;
	touch_mnt_namespace(mnt->mnt_ns);
	unlock_mount_hash();
}