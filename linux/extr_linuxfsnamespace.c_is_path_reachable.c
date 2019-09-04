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
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/ * mnt; } ;
struct mount {int /*<<< orphan*/  mnt; struct mount* mnt_parent; struct dentry* mnt_mountpoint; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_subdir (struct dentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ mnt_has_parent (struct mount*) ; 

bool is_path_reachable(struct mount *mnt, struct dentry *dentry,
			 const struct path *root)
{
	while (&mnt->mnt != root->mnt && mnt_has_parent(mnt)) {
		dentry = mnt->mnt_mountpoint;
		mnt = mnt->mnt_parent;
	}
	return &mnt->mnt == root->mnt && is_subdir(dentry, root->dentry);
}