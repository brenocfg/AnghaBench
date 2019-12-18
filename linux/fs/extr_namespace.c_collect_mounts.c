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
 int CL_COPY_ALL ; 
 int CL_PRIVATE ; 
 int /*<<< orphan*/  EINVAL ; 
 struct vfsmount* ERR_CAST (struct mount*) ; 
 struct mount* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct mount*) ; 
 int /*<<< orphan*/  check_mnt (int /*<<< orphan*/ ) ; 
 struct mount* copy_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  namespace_lock () ; 
 int /*<<< orphan*/  namespace_unlock () ; 
 int /*<<< orphan*/  real_mount (int /*<<< orphan*/ ) ; 

struct vfsmount *collect_mounts(const struct path *path)
{
	struct mount *tree;
	namespace_lock();
	if (!check_mnt(real_mount(path->mnt)))
		tree = ERR_PTR(-EINVAL);
	else
		tree = copy_tree(real_mount(path->mnt), path->dentry,
				 CL_COPY_ALL | CL_PRIVATE);
	namespace_unlock();
	if (IS_ERR(tree))
		return ERR_CAST(tree);
	return &tree->mnt;
}