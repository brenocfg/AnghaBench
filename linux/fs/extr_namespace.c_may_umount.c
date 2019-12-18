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
struct vfsmount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 int /*<<< orphan*/  namespace_sem ; 
 scalar_t__ propagate_mount_busy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  real_mount (struct vfsmount*) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int may_umount(struct vfsmount *mnt)
{
	int ret = 1;
	down_read(&namespace_sem);
	lock_mount_hash();
	if (propagate_mount_busy(real_mount(mnt), 2))
		ret = 0;
	unlock_mount_hash();
	up_read(&namespace_sem);
	return ret;
}