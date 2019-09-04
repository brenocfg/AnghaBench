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
struct mount {int /*<<< orphan*/  mnt_list; struct mnt_namespace* mnt_ns; } ;
struct mnt_namespace {int /*<<< orphan*/  list; int /*<<< orphan*/  mounts; struct mount* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct mnt_namespace*) ; 
 struct mnt_namespace* alloc_mnt_ns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 struct mount* real_mount (struct vfsmount*) ; 

__attribute__((used)) static struct mnt_namespace *create_mnt_ns(struct vfsmount *m)
{
	struct mnt_namespace *new_ns = alloc_mnt_ns(&init_user_ns);
	if (!IS_ERR(new_ns)) {
		struct mount *mnt = real_mount(m);
		mnt->mnt_ns = new_ns;
		new_ns->root = mnt;
		new_ns->mounts++;
		list_add(&mnt->mnt_list, &new_ns->list);
	} else {
		mntput(m);
	}
	return new_ns;
}