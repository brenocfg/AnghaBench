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
struct TYPE_2__ {int /*<<< orphan*/  mnt_flags; } ;
struct mount {TYPE_1__ mnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_READONLY ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 

__attribute__((used)) static int __mnt_unmake_readonly(struct mount *mnt)
{
	lock_mount_hash();
	mnt->mnt.mnt_flags &= ~MNT_READONLY;
	unlock_mount_hash();
	return 0;
}