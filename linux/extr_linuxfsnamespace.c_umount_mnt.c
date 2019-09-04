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
struct mount {int /*<<< orphan*/  mnt_mountpoint; int /*<<< orphan*/  mnt_ex_mountpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  unhash_mnt (struct mount*) ; 

__attribute__((used)) static void umount_mnt(struct mount *mnt)
{
	/* old mountpoint will be dropped when we can do that */
	mnt->mnt_ex_mountpoint = mnt->mnt_mountpoint;
	unhash_mnt(mnt);
}