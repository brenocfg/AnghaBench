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
struct mountpoint {int dummy; } ;
struct mount {int /*<<< orphan*/  mnt_hash; int /*<<< orphan*/  mnt_mp_list; int /*<<< orphan*/  mnt_child; struct mount* mnt_parent; struct dentry* mnt_mountpoint; struct mountpoint* mnt_mp; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct dentry {int /*<<< orphan*/  d_lock; TYPE_1__ d_lockref; } ;

/* Variables and functions */
 int /*<<< orphan*/  attach_mnt (struct mount*,struct mount*,struct mountpoint*) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mnt_add_count (struct mount*,int) ; 
 int /*<<< orphan*/  put_mountpoint (struct mountpoint*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mnt_change_mountpoint(struct mount *parent, struct mountpoint *mp, struct mount *mnt)
{
	struct mountpoint *old_mp = mnt->mnt_mp;
	struct dentry *old_mountpoint = mnt->mnt_mountpoint;
	struct mount *old_parent = mnt->mnt_parent;

	list_del_init(&mnt->mnt_child);
	hlist_del_init(&mnt->mnt_mp_list);
	hlist_del_init_rcu(&mnt->mnt_hash);

	attach_mnt(mnt, parent, mp);

	put_mountpoint(old_mp);

	/*
	 * Safely avoid even the suggestion this code might sleep or
	 * lock the mount hash by taking advantage of the knowledge that
	 * mnt_change_mountpoint will not release the final reference
	 * to a mountpoint.
	 *
	 * During mounting, the mount passed in as the parent mount will
	 * continue to use the old mountpoint and during unmounting, the
	 * old mountpoint will continue to exist until namespace_unlock,
	 * which happens well after mnt_change_mountpoint.
	 */
	spin_lock(&old_mountpoint->d_lock);
	old_mountpoint->d_lockref.count--;
	spin_unlock(&old_mountpoint->d_lock);

	mnt_add_count(old_parent, -1);
}