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
struct mount {int /*<<< orphan*/  mnt_mounts; int /*<<< orphan*/  mnt_mountpoint; int /*<<< orphan*/  mnt; struct mount* mnt_parent; } ;

/* Variables and functions */
 struct mount* __lookup_mnt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int do_refcount_check (struct mount*,int) ; 
 struct mount* find_topper (struct mount*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct mount* propagation_next (struct mount*,struct mount*) ; 

int propagate_mount_busy(struct mount *mnt, int refcnt)
{
	struct mount *m, *child, *topper;
	struct mount *parent = mnt->mnt_parent;

	if (mnt == parent)
		return do_refcount_check(mnt, refcnt);

	/*
	 * quickly check if the current mount can be unmounted.
	 * If not, we don't have to go checking for all other
	 * mounts
	 */
	if (!list_empty(&mnt->mnt_mounts) || do_refcount_check(mnt, refcnt))
		return 1;

	for (m = propagation_next(parent, parent); m;
	     		m = propagation_next(m, parent)) {
		int count = 1;
		child = __lookup_mnt(&m->mnt, mnt->mnt_mountpoint);
		if (!child)
			continue;

		/* Is there exactly one mount on the child that covers
		 * it completely whose reference should be ignored?
		 */
		topper = find_topper(child);
		if (topper)
			count += 1;
		else if (!list_empty(&child->mnt_mounts))
			continue;

		if (do_refcount_check(child, count))
			return 1;
	}
	return 0;
}