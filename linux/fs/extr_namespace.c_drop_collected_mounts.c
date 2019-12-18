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
 int /*<<< orphan*/  lock_mount_hash () ; 
 int /*<<< orphan*/  namespace_lock () ; 
 int /*<<< orphan*/  namespace_unlock () ; 
 int /*<<< orphan*/  real_mount (struct vfsmount*) ; 
 int /*<<< orphan*/  umount_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 

void drop_collected_mounts(struct vfsmount *mnt)
{
	namespace_lock();
	lock_mount_hash();
	umount_tree(real_mount(mnt), 0);
	unlock_mount_hash();
	namespace_unlock();
}