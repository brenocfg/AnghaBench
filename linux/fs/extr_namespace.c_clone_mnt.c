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
struct super_block {int /*<<< orphan*/  s_mounts; int /*<<< orphan*/  s_active; } ;
struct TYPE_2__ {int mnt_flags; int /*<<< orphan*/  mnt_root; struct super_block* mnt_sb; } ;
struct mount {int /*<<< orphan*/  mnt_expire; struct mount* mnt_master; int /*<<< orphan*/  mnt_slave; int /*<<< orphan*/  mnt_share; int /*<<< orphan*/  mnt_slave_list; int /*<<< orphan*/  mnt_instance; struct mount* mnt_parent; TYPE_1__ mnt; int /*<<< orphan*/  mnt_mountpoint; scalar_t__ mnt_group_id; int /*<<< orphan*/  mnt_devname; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_MNT_SHARED (struct mount*) ; 
 int CL_EXPIRE ; 
 int CL_MAKE_SHARED ; 
 int CL_PRIVATE ; 
 int CL_SHARED_TO_SLAVE ; 
 int CL_SLAVE ; 
 int ENOMEM ; 
 struct mount* ERR_PTR (int) ; 
 scalar_t__ IS_MNT_SHARED (struct mount*) ; 
 scalar_t__ IS_MNT_SLAVE (struct mount*) ; 
 int MNT_INTERNAL ; 
 int MNT_MARKED ; 
 int MNT_WRITE_HOLD ; 
 struct mount* alloc_vfsmnt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  free_vfsmnt (struct mount*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 int mnt_alloc_group_id (struct mount*) ; 
 int /*<<< orphan*/  mnt_free_id (struct mount*) ; 
 int /*<<< orphan*/  set_mnt_shared (struct mount*) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 

__attribute__((used)) static struct mount *clone_mnt(struct mount *old, struct dentry *root,
					int flag)
{
	struct super_block *sb = old->mnt.mnt_sb;
	struct mount *mnt;
	int err;

	mnt = alloc_vfsmnt(old->mnt_devname);
	if (!mnt)
		return ERR_PTR(-ENOMEM);

	if (flag & (CL_SLAVE | CL_PRIVATE | CL_SHARED_TO_SLAVE))
		mnt->mnt_group_id = 0; /* not a peer of original */
	else
		mnt->mnt_group_id = old->mnt_group_id;

	if ((flag & CL_MAKE_SHARED) && !mnt->mnt_group_id) {
		err = mnt_alloc_group_id(mnt);
		if (err)
			goto out_free;
	}

	mnt->mnt.mnt_flags = old->mnt.mnt_flags;
	mnt->mnt.mnt_flags &= ~(MNT_WRITE_HOLD|MNT_MARKED|MNT_INTERNAL);

	atomic_inc(&sb->s_active);
	mnt->mnt.mnt_sb = sb;
	mnt->mnt.mnt_root = dget(root);
	mnt->mnt_mountpoint = mnt->mnt.mnt_root;
	mnt->mnt_parent = mnt;
	lock_mount_hash();
	list_add_tail(&mnt->mnt_instance, &sb->s_mounts);
	unlock_mount_hash();

	if ((flag & CL_SLAVE) ||
	    ((flag & CL_SHARED_TO_SLAVE) && IS_MNT_SHARED(old))) {
		list_add(&mnt->mnt_slave, &old->mnt_slave_list);
		mnt->mnt_master = old;
		CLEAR_MNT_SHARED(mnt);
	} else if (!(flag & CL_PRIVATE)) {
		if ((flag & CL_MAKE_SHARED) || IS_MNT_SHARED(old))
			list_add(&mnt->mnt_share, &old->mnt_share);
		if (IS_MNT_SLAVE(old))
			list_add(&mnt->mnt_slave, &old->mnt_slave);
		mnt->mnt_master = old->mnt_master;
	} else {
		CLEAR_MNT_SHARED(mnt);
	}
	if (flag & CL_MAKE_SHARED)
		set_mnt_shared(mnt);

	/* stick the duplicate mount on the same expiry list
	 * as the original if that was on one */
	if (flag & CL_EXPIRE) {
		if (!list_empty(&old->mnt_expire))
			list_add(&mnt->mnt_expire, &old->mnt_expire);
	}

	return mnt;

 out_free:
	mnt_free_id(mnt);
	free_vfsmnt(mnt);
	return ERR_PTR(err);
}