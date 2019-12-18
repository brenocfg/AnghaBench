#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct mnt_namespace {int dummy; } ;
struct TYPE_3__ {struct mnt_namespace* mnt_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMOUNT_CONNECTED ; 
 int /*<<< orphan*/  free_mnt_ns (struct mnt_namespace*) ; 
 scalar_t__ is_anon_ns (struct mnt_namespace*) ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 int /*<<< orphan*/  namespace_lock () ; 
 int /*<<< orphan*/  namespace_unlock () ; 
 TYPE_1__* real_mount (struct vfsmount*) ; 
 int /*<<< orphan*/  umount_tree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 

void dissolve_on_fput(struct vfsmount *mnt)
{
	struct mnt_namespace *ns;
	namespace_lock();
	lock_mount_hash();
	ns = real_mount(mnt)->mnt_ns;
	if (ns) {
		if (is_anon_ns(ns))
			umount_tree(real_mount(mnt), UMOUNT_CONNECTED);
		else
			ns = NULL;
	}
	unlock_mount_hash();
	namespace_unlock();
	if (ns)
		free_mnt_ns(ns);
}