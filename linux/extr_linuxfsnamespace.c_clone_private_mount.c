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
struct vfsmount {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;
struct mount {struct vfsmount mnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_PRIVATE ; 
 int /*<<< orphan*/  EINVAL ; 
 struct vfsmount* ERR_CAST (struct mount*) ; 
 struct vfsmount* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct mount*) ; 
 scalar_t__ IS_MNT_UNBINDABLE (struct mount*) ; 
 struct mount* clone_mnt (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mount* real_mount (int /*<<< orphan*/ ) ; 

struct vfsmount *clone_private_mount(const struct path *path)
{
	struct mount *old_mnt = real_mount(path->mnt);
	struct mount *new_mnt;

	if (IS_MNT_UNBINDABLE(old_mnt))
		return ERR_PTR(-EINVAL);

	new_mnt = clone_mnt(old_mnt, path->dentry, CL_PRIVATE);
	if (IS_ERR(new_mnt))
		return ERR_CAST(new_mnt);

	return &new_mnt->mnt;
}