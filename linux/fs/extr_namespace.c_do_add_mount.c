#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct path {scalar_t__ dentry; TYPE_2__* mnt; } ;
struct mountpoint {int dummy; } ;
struct TYPE_3__ {scalar_t__ mnt_sb; int mnt_flags; int /*<<< orphan*/  mnt_root; } ;
struct mount {TYPE_1__ mnt; int /*<<< orphan*/  mnt_ns; } ;
struct TYPE_4__ {scalar_t__ mnt_sb; scalar_t__ mnt_root; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct mountpoint*) ; 
 int MNT_INTERNAL_FLAGS ; 
 int MNT_SHRINKABLE ; 
 int PTR_ERR (struct mountpoint*) ; 
 int /*<<< orphan*/  check_mnt (struct mount*) ; 
 scalar_t__ d_is_symlink (int /*<<< orphan*/ ) ; 
 int graft_tree (struct mount*,struct mount*,struct mountpoint*) ; 
 struct mountpoint* lock_mount (struct path*) ; 
 struct mount* real_mount (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_mount (struct mountpoint*) ; 

__attribute__((used)) static int do_add_mount(struct mount *newmnt, struct path *path, int mnt_flags)
{
	struct mountpoint *mp;
	struct mount *parent;
	int err;

	mnt_flags &= ~MNT_INTERNAL_FLAGS;

	mp = lock_mount(path);
	if (IS_ERR(mp))
		return PTR_ERR(mp);

	parent = real_mount(path->mnt);
	err = -EINVAL;
	if (unlikely(!check_mnt(parent))) {
		/* that's acceptable only for automounts done in private ns */
		if (!(mnt_flags & MNT_SHRINKABLE))
			goto unlock;
		/* ... and for those we'd better have mountpoint still alive */
		if (!parent->mnt_ns)
			goto unlock;
	}

	/* Refuse the same filesystem on the same mount point */
	err = -EBUSY;
	if (path->mnt->mnt_sb == newmnt->mnt.mnt_sb &&
	    path->mnt->mnt_root == path->dentry)
		goto unlock;

	err = -EINVAL;
	if (d_is_symlink(newmnt->mnt.mnt_root))
		goto unlock;

	newmnt->mnt.mnt_flags = mnt_flags;
	err = graft_tree(newmnt, parent, mp);

unlock:
	unlock_mount(mp);
	return err;
}