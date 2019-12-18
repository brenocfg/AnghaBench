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
struct vfsmount {scalar_t__ mnt_sb; scalar_t__ mnt_root; } ;
struct path {scalar_t__ dentry; TYPE_1__* mnt; } ;
struct mount {int /*<<< orphan*/  mnt_expire; } ;
struct TYPE_2__ {scalar_t__ mnt_sb; int mnt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ELOOP ; 
 int MNT_SHRINKABLE ; 
 int do_add_mount (struct mount*,struct path*,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int mnt_get_count (struct mount*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  namespace_lock () ; 
 int /*<<< orphan*/  namespace_unlock () ; 
 struct mount* real_mount (struct vfsmount*) ; 

int finish_automount(struct vfsmount *m, struct path *path)
{
	struct mount *mnt = real_mount(m);
	int err;
	/* The new mount record should have at least 2 refs to prevent it being
	 * expired before we get a chance to add it
	 */
	BUG_ON(mnt_get_count(mnt) < 2);

	if (m->mnt_sb == path->mnt->mnt_sb &&
	    m->mnt_root == path->dentry) {
		err = -ELOOP;
		goto fail;
	}

	err = do_add_mount(mnt, path, path->mnt->mnt_flags | MNT_SHRINKABLE);
	if (!err)
		return 0;
fail:
	/* remove m from any expiration list it may be on */
	if (!list_empty(&mnt->mnt_expire)) {
		namespace_lock();
		list_del_init(&mnt->mnt_expire);
		namespace_unlock();
	}
	mntput(m);
	mntput(m);
	return err;
}