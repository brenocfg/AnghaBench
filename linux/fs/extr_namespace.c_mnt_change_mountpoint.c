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
struct mountpoint {int dummy; } ;
struct mount {int /*<<< orphan*/  mnt_hash; int /*<<< orphan*/  mnt_mp_list; int /*<<< orphan*/  mnt_child; struct mount* mnt_parent; struct mountpoint* mnt_mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  attach_mnt (struct mount*,struct mount*,struct mountpoint*) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mnt_add_count (struct mount*,int) ; 
 int /*<<< orphan*/  put_mountpoint (struct mountpoint*) ; 

void mnt_change_mountpoint(struct mount *parent, struct mountpoint *mp, struct mount *mnt)
{
	struct mountpoint *old_mp = mnt->mnt_mp;
	struct mount *old_parent = mnt->mnt_parent;

	list_del_init(&mnt->mnt_child);
	hlist_del_init(&mnt->mnt_mp_list);
	hlist_del_init_rcu(&mnt->mnt_hash);

	attach_mnt(mnt, parent, mp);

	put_mountpoint(old_mp);
	mnt_add_count(old_parent, -1);
}