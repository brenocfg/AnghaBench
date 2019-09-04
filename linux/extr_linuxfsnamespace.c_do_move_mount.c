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
struct TYPE_3__ {int mnt_flags; } ;
struct mount {int /*<<< orphan*/  mnt_expire; struct mount* mnt_parent; TYPE_1__ mnt; } ;
struct TYPE_4__ {scalar_t__ mnt_root; } ;

/* Variables and functions */
 int EINVAL ; 
 int ELOOP ; 
 scalar_t__ IS_ERR (struct mountpoint*) ; 
 scalar_t__ IS_MNT_SHARED (struct mount*) ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 int MNT_LOCKED ; 
 int PTR_ERR (struct mountpoint*) ; 
 int attach_recursive_mnt (struct mount*,struct mount*,struct mountpoint*,struct path*) ; 
 int /*<<< orphan*/  check_mnt (struct mount*) ; 
 scalar_t__ d_is_dir (scalar_t__) ; 
 int kern_path (char const*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct mountpoint* lock_mount (struct path*) ; 
 scalar_t__ mnt_has_parent (struct mount*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 struct mount* real_mount (TYPE_2__*) ; 
 scalar_t__ tree_contains_unbindable (struct mount*) ; 
 int /*<<< orphan*/  unlock_mount (struct mountpoint*) ; 

__attribute__((used)) static int do_move_mount(struct path *path, const char *old_name)
{
	struct path old_path, parent_path;
	struct mount *p;
	struct mount *old;
	struct mountpoint *mp;
	int err;
	if (!old_name || !*old_name)
		return -EINVAL;
	err = kern_path(old_name, LOOKUP_FOLLOW, &old_path);
	if (err)
		return err;

	mp = lock_mount(path);
	err = PTR_ERR(mp);
	if (IS_ERR(mp))
		goto out;

	old = real_mount(old_path.mnt);
	p = real_mount(path->mnt);

	err = -EINVAL;
	if (!check_mnt(p) || !check_mnt(old))
		goto out1;

	if (old->mnt.mnt_flags & MNT_LOCKED)
		goto out1;

	err = -EINVAL;
	if (old_path.dentry != old_path.mnt->mnt_root)
		goto out1;

	if (!mnt_has_parent(old))
		goto out1;

	if (d_is_dir(path->dentry) !=
	      d_is_dir(old_path.dentry))
		goto out1;
	/*
	 * Don't move a mount residing in a shared parent.
	 */
	if (IS_MNT_SHARED(old->mnt_parent))
		goto out1;
	/*
	 * Don't move a mount tree containing unbindable mounts to a destination
	 * mount which is shared.
	 */
	if (IS_MNT_SHARED(p) && tree_contains_unbindable(old))
		goto out1;
	err = -ELOOP;
	for (; mnt_has_parent(p); p = p->mnt_parent)
		if (p == old)
			goto out1;

	err = attach_recursive_mnt(old, real_mount(path->mnt), mp, &parent_path);
	if (err)
		goto out1;

	/* if the mount is moved, it should no longer be expire
	 * automatically */
	list_del_init(&old->mnt_expire);
out1:
	unlock_mount(mp);
out:
	if (!err)
		path_put(&parent_path);
	path_put(&old_path);
	return err;
}