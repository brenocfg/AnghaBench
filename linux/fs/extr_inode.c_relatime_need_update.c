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
struct vfsmount {int mnt_flags; } ;
struct timespec64 {scalar_t__ tv_sec; } ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;
struct inode {TYPE_1__ i_atime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;

/* Variables and functions */
 int MNT_RELATIME ; 
 scalar_t__ timespec64_compare (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int relatime_need_update(struct vfsmount *mnt, struct inode *inode,
			     struct timespec64 now)
{

	if (!(mnt->mnt_flags & MNT_RELATIME))
		return 1;
	/*
	 * Is mtime younger than atime? If yes, update atime:
	 */
	if (timespec64_compare(&inode->i_mtime, &inode->i_atime) >= 0)
		return 1;
	/*
	 * Is ctime younger than atime? If yes, update atime:
	 */
	if (timespec64_compare(&inode->i_ctime, &inode->i_atime) >= 0)
		return 1;

	/*
	 * Is the previous atime value older than a day? If yes,
	 * update atime:
	 */
	if ((long)(now.tv_sec - inode->i_atime.tv_sec) >= 24*60*60)
		return 1;
	/*
	 * Good, we can skip the atime update:
	 */
	return 0;
}