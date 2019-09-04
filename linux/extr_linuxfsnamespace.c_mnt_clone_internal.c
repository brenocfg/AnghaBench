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
struct vfsmount {int /*<<< orphan*/  mnt_flags; } ;
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;
struct mount {struct vfsmount mnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_PRIVATE ; 
 struct vfsmount* ERR_CAST (struct mount*) ; 
 scalar_t__ IS_ERR (struct mount*) ; 
 int /*<<< orphan*/  MNT_INTERNAL ; 
 struct mount* clone_mnt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_mount (int /*<<< orphan*/ ) ; 

struct vfsmount *mnt_clone_internal(const struct path *path)
{
	struct mount *p;
	p = clone_mnt(real_mount(path->mnt), path->dentry, CL_PRIVATE);
	if (IS_ERR(p))
		return ERR_CAST(p);
	p->mnt.mnt_flags |= MNT_INTERNAL;
	return &p->mnt;
}