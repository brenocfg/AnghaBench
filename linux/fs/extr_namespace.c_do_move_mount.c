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
struct path {scalar_t__ dentry; TYPE_1__* mnt; } ;
struct mountpoint {int dummy; } ;
struct TYPE_4__ {int mnt_flags; } ;
struct mount {int /*<<< orphan*/  mnt_expire; struct mount* mnt_parent; TYPE_2__ mnt; struct mnt_namespace* mnt_ns; struct mountpoint* mnt_mp; } ;
struct mnt_namespace {int dummy; } ;
struct TYPE_3__ {scalar_t__ mnt_root; } ;

/* Variables and functions */
 int EINVAL ; 
 int ELOOP ; 
 scalar_t__ IS_ERR (struct mountpoint*) ; 
 scalar_t__ IS_MNT_SHARED (struct mount*) ; 
 int MNT_LOCKED ; 
 int PTR_ERR (struct mountpoint*) ; 
 int attach_recursive_mnt (struct mount*,struct mount*,struct mountpoint*,int) ; 
 int /*<<< orphan*/  check_for_nsfs_mounts (struct mount*) ; 
 int /*<<< orphan*/  check_mnt (struct mount*) ; 
 scalar_t__ d_is_dir (scalar_t__) ; 
 int /*<<< orphan*/  free_mnt_ns (struct mnt_namespace*) ; 
 int /*<<< orphan*/  is_anon_ns (struct mnt_namespace*) ; 
 int /*<<< orphan*/  is_mounted (TYPE_2__*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct mountpoint* lock_mount (struct path*) ; 
 int mnt_has_parent (struct mount*) ; 
 int /*<<< orphan*/  mntput_no_expire (struct mount*) ; 
 int /*<<< orphan*/  put_mountpoint (struct mountpoint*) ; 
 struct mount* real_mount (TYPE_1__*) ; 
 scalar_t__ tree_contains_unbindable (struct mount*) ; 
 int /*<<< orphan*/  unlock_mount (struct mountpoint*) ; 

__attribute__((used)) static int do_move_mount(struct path *old_path, struct path *new_path)
{
	struct mnt_namespace *ns;
	struct mount *p;
	struct mount *old;
	struct mount *parent;
	struct mountpoint *mp, *old_mp;
	int err;
	bool attached;

	mp = lock_mount(new_path);
	if (IS_ERR(mp))
		return PTR_ERR(mp);

	old = real_mount(old_path->mnt);
	p = real_mount(new_path->mnt);
	parent = old->mnt_parent;
	attached = mnt_has_parent(old);
	old_mp = old->mnt_mp;
	ns = old->mnt_ns;

	err = -EINVAL;
	/* The mountpoint must be in our namespace. */
	if (!check_mnt(p))
		goto out;

	/* The thing moved must be mounted... */
	if (!is_mounted(&old->mnt))
		goto out;

	/* ... and either ours or the root of anon namespace */
	if (!(attached ? check_mnt(old) : is_anon_ns(ns)))
		goto out;

	if (old->mnt.mnt_flags & MNT_LOCKED)
		goto out;

	if (old_path->dentry != old_path->mnt->mnt_root)
		goto out;

	if (d_is_dir(new_path->dentry) !=
	    d_is_dir(old_path->dentry))
		goto out;
	/*
	 * Don't move a mount residing in a shared parent.
	 */
	if (attached && IS_MNT_SHARED(parent))
		goto out;
	/*
	 * Don't move a mount tree containing unbindable mounts to a destination
	 * mount which is shared.
	 */
	if (IS_MNT_SHARED(p) && tree_contains_unbindable(old))
		goto out;
	err = -ELOOP;
	if (!check_for_nsfs_mounts(old))
		goto out;
	for (; mnt_has_parent(p); p = p->mnt_parent)
		if (p == old)
			goto out;

	err = attach_recursive_mnt(old, real_mount(new_path->mnt), mp,
				   attached);
	if (err)
		goto out;

	/* if the mount is moved, it should no longer be expire
	 * automatically */
	list_del_init(&old->mnt_expire);
	if (attached)
		put_mountpoint(old_mp);
out:
	unlock_mount(mp);
	if (!err) {
		if (attached)
			mntput_no_expire(parent);
		else
			free_mnt_ns(ns);
	}
	return err;
}