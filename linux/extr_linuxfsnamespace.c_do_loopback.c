#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_2__* dentry; int /*<<< orphan*/  mnt; } ;
struct TYPE_6__ {int /*<<< orphan*/  mnt_flags; } ;
struct mountpoint {TYPE_1__ mnt; } ;
struct mount {TYPE_1__ mnt; } ;
struct TYPE_7__ {int /*<<< orphan*/ * d_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_COPY_MNT_NS_FILE ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct mountpoint*) ; 
 scalar_t__ IS_MNT_UNBINDABLE (struct mountpoint*) ; 
 int LOOKUP_AUTOMOUNT ; 
 int LOOKUP_FOLLOW ; 
 int /*<<< orphan*/  MNT_LOCKED ; 
 int PTR_ERR (struct mountpoint*) ; 
 int /*<<< orphan*/  UMOUNT_SYNC ; 
 int /*<<< orphan*/  check_mnt (struct mountpoint*) ; 
 struct mountpoint* clone_mnt (struct mountpoint*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct mountpoint* copy_tree (struct mountpoint*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int graft_tree (struct mountpoint*,struct mountpoint*,struct mountpoint*) ; 
 scalar_t__ has_locked_children (struct mountpoint*,TYPE_2__*) ; 
 int kern_path (char const*,int,struct path*) ; 
 struct mountpoint* lock_mount (struct path*) ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 scalar_t__ mnt_ns_loop (TYPE_2__*) ; 
 int /*<<< orphan*/  ns_dentry_operations ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 struct mountpoint* real_mount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umount_tree (struct mountpoint*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_mount (struct mountpoint*) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 

__attribute__((used)) static int do_loopback(struct path *path, const char *old_name,
				int recurse)
{
	struct path old_path;
	struct mount *mnt = NULL, *old, *parent;
	struct mountpoint *mp;
	int err;
	if (!old_name || !*old_name)
		return -EINVAL;
	err = kern_path(old_name, LOOKUP_FOLLOW|LOOKUP_AUTOMOUNT, &old_path);
	if (err)
		return err;

	err = -EINVAL;
	if (mnt_ns_loop(old_path.dentry))
		goto out;

	mp = lock_mount(path);
	err = PTR_ERR(mp);
	if (IS_ERR(mp))
		goto out;

	old = real_mount(old_path.mnt);
	parent = real_mount(path->mnt);

	err = -EINVAL;
	if (IS_MNT_UNBINDABLE(old))
		goto out2;

	if (!check_mnt(parent))
		goto out2;

	if (!check_mnt(old) && old_path.dentry->d_op != &ns_dentry_operations)
		goto out2;

	if (!recurse && has_locked_children(old, old_path.dentry))
		goto out2;

	if (recurse)
		mnt = copy_tree(old, old_path.dentry, CL_COPY_MNT_NS_FILE);
	else
		mnt = clone_mnt(old, old_path.dentry, 0);

	if (IS_ERR(mnt)) {
		err = PTR_ERR(mnt);
		goto out2;
	}

	mnt->mnt.mnt_flags &= ~MNT_LOCKED;

	err = graft_tree(mnt, parent, mp);
	if (err) {
		lock_mount_hash();
		umount_tree(mnt, UMOUNT_SYNC);
		unlock_mount_hash();
	}
out2:
	unlock_mount(mp);
out:
	path_put(&old_path);
	return err;
}