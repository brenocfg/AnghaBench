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
struct mountpoint {int /*<<< orphan*/  m_list; int /*<<< orphan*/  m_dentry; int /*<<< orphan*/  m_count; } ;
struct mount {int /*<<< orphan*/  mnt_mp_list; struct mountpoint* mnt_mp; struct mount* mnt_parent; int /*<<< orphan*/  mnt_mountpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mnt_add_count (struct mount*,int) ; 

void mnt_set_mountpoint(struct mount *mnt,
			struct mountpoint *mp,
			struct mount *child_mnt)
{
	mp->m_count++;
	mnt_add_count(mnt, 1);	/* essentially, that's mntget */
	child_mnt->mnt_mountpoint = mp->m_dentry;
	child_mnt->mnt_parent = mnt;
	child_mnt->mnt_mp = mp;
	hlist_add_head(&child_mnt->mnt_mp_list, &mp->m_list);
}