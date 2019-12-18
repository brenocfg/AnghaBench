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
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 scalar_t__ mnt_get_count (struct mount*) ; 
 struct mount* next_mnt (struct mount*,struct mount*) ; 
 struct mount* real_mount (struct vfsmount*) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 

int may_umount_tree(struct vfsmount *m)
{
	struct mount *mnt = real_mount(m);
	int actual_refs = 0;
	int minimum_refs = 0;
	struct mount *p;
	BUG_ON(!m);

	/* write lock needed for mnt_get_count */
	lock_mount_hash();
	for (p = mnt; p; p = next_mnt(p, mnt)) {
		actual_refs += mnt_get_count(p);
		minimum_refs += 2;
	}
	unlock_mount_hash();

	if (actual_refs > minimum_refs)
		return 0;

	return 1;
}