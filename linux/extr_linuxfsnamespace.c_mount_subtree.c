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
struct vfsmount {int /*<<< orphan*/  mnt_root; } ;
struct super_block {int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_active; } ;
struct path {struct dentry* dentry; TYPE_1__* mnt; } ;
struct mnt_namespace {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct super_block* mnt_sb; } ;

/* Variables and functions */
 struct dentry* ERR_CAST (struct mnt_namespace*) ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mnt_namespace*) ; 
 int LOOKUP_AUTOMOUNT ; 
 int LOOKUP_FOLLOW ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct mnt_namespace* create_mnt_ns (struct vfsmount*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mntput (TYPE_1__*) ; 
 int /*<<< orphan*/  put_mnt_ns (struct mnt_namespace*) ; 
 int vfs_path_lookup (int /*<<< orphan*/ ,struct vfsmount*,char const*,int,struct path*) ; 

struct dentry *mount_subtree(struct vfsmount *mnt, const char *name)
{
	struct mnt_namespace *ns;
	struct super_block *s;
	struct path path;
	int err;

	ns = create_mnt_ns(mnt);
	if (IS_ERR(ns))
		return ERR_CAST(ns);

	err = vfs_path_lookup(mnt->mnt_root, mnt,
			name, LOOKUP_FOLLOW|LOOKUP_AUTOMOUNT, &path);

	put_mnt_ns(ns);

	if (err)
		return ERR_PTR(err);

	/* trade a vfsmount reference for active sb one */
	s = path.mnt->mnt_sb;
	atomic_inc(&s->s_active);
	mntput(path.mnt);
	/* lock the sucker */
	down_write(&s->s_umount);
	/* ... and return the root of (sub)tree on it */
	return path.dentry;
}