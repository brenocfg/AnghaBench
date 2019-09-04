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
struct mount {TYPE_1__ mnt; int /*<<< orphan*/  mnt_mountpoint; struct mount* mnt_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MNT_LOCKED ; 
 struct mount* __lookup_mnt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct mount* propagation_next (struct mount*,struct mount*) ; 

void propagate_mount_unlock(struct mount *mnt)
{
	struct mount *parent = mnt->mnt_parent;
	struct mount *m, *child;

	BUG_ON(parent == mnt);

	for (m = propagation_next(parent, parent); m;
			m = propagation_next(m, parent)) {
		child = __lookup_mnt(&m->mnt, mnt->mnt_mountpoint);
		if (child)
			child->mnt.mnt_flags &= ~MNT_LOCKED;
	}
}