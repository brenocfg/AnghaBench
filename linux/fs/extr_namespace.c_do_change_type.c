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
struct path {scalar_t__ dentry; TYPE_1__* mnt; } ;
struct mount {int dummy; } ;
struct TYPE_2__ {scalar_t__ mnt_root; } ;

/* Variables and functions */
 int EINVAL ; 
 int MS_REC ; 
 int MS_SHARED ; 
 int /*<<< orphan*/  change_mnt_propagation (struct mount*,int) ; 
 int flags_to_propagation_type (int) ; 
 int invent_group_ids (struct mount*,int) ; 
 int /*<<< orphan*/  lock_mount_hash () ; 
 int /*<<< orphan*/  namespace_lock () ; 
 int /*<<< orphan*/  namespace_unlock () ; 
 struct mount* next_mnt (struct mount*,struct mount*) ; 
 struct mount* real_mount (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_mount_hash () ; 

__attribute__((used)) static int do_change_type(struct path *path, int ms_flags)
{
	struct mount *m;
	struct mount *mnt = real_mount(path->mnt);
	int recurse = ms_flags & MS_REC;
	int type;
	int err = 0;

	if (path->dentry != path->mnt->mnt_root)
		return -EINVAL;

	type = flags_to_propagation_type(ms_flags);
	if (!type)
		return -EINVAL;

	namespace_lock();
	if (type == MS_SHARED) {
		err = invent_group_ids(mnt, recurse);
		if (err)
			goto out_unlock;
	}

	lock_mount_hash();
	for (m = mnt; m; m = (recurse ? next_mnt(m, mnt) : NULL))
		change_mnt_propagation(m, type);
	unlock_mount_hash();

 out_unlock:
	namespace_unlock();
	return err;
}