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
struct vfsmount {int mnt_flags; int /*<<< orphan*/  mnt_sb; } ;

/* Variables and functions */
 int MNT_READONLY ; 
 scalar_t__ sb_rdonly (int /*<<< orphan*/ ) ; 

int __mnt_is_readonly(struct vfsmount *mnt)
{
	if (mnt->mnt_flags & MNT_READONLY)
		return 1;
	if (sb_rdonly(mnt->mnt_sb))
		return 1;
	return 0;
}