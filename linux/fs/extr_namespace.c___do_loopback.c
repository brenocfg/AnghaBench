#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_2__* dentry; int /*<<< orphan*/  mnt; } ;
struct TYPE_5__ {int /*<<< orphan*/  mnt_flags; } ;
struct mount {TYPE_1__ mnt; } ;
struct TYPE_6__ {int /*<<< orphan*/ * d_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_COPY_MNT_NS_FILE ; 
 int /*<<< orphan*/  EINVAL ; 
 struct mount* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct mount*) ; 
 scalar_t__ IS_MNT_UNBINDABLE (struct mount*) ; 
 int /*<<< orphan*/  MNT_LOCKED ; 
 int /*<<< orphan*/  check_mnt (struct mount*) ; 
 struct mount* clone_mnt (struct mount*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct mount* copy_tree (struct mount*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ has_locked_children (struct mount*,TYPE_2__*) ; 
 int /*<<< orphan*/  ns_dentry_operations ; 
 struct mount* real_mount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mount *__do_loopback(struct path *old_path, int recurse)
{
	struct mount *mnt = ERR_PTR(-EINVAL), *old = real_mount(old_path->mnt);

	if (IS_MNT_UNBINDABLE(old))
		return mnt;

	if (!check_mnt(old) && old_path->dentry->d_op != &ns_dentry_operations)
		return mnt;

	if (!recurse && has_locked_children(old, old_path->dentry))
		return mnt;

	if (recurse)
		mnt = copy_tree(old, old_path->dentry, CL_COPY_MNT_NS_FILE);
	else
		mnt = clone_mnt(old, old_path->dentry, 0);

	if (!IS_ERR(mnt))
		mnt->mnt.mnt_flags &= ~MNT_LOCKED;

	return mnt;
}