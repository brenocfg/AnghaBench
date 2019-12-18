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
struct vfsmount {struct super_block* mnt_sb; int /*<<< orphan*/  mnt_root; } ;
struct super_block {int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_active; } ;
struct path {struct dentry* dentry; struct vfsmount* mnt; } ;
struct mount {int /*<<< orphan*/  mnt_list; struct mnt_namespace* mnt_ns; } ;
struct mnt_namespace {int /*<<< orphan*/  list; int /*<<< orphan*/  mounts; struct mount* root; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* ERR_CAST (struct mnt_namespace*) ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mnt_namespace*) ; 
 int LOOKUP_AUTOMOUNT ; 
 int LOOKUP_FOLLOW ; 
 struct mnt_namespace* alloc_mnt_ns (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  put_mnt_ns (struct mnt_namespace*) ; 
 struct mount* real_mount (struct vfsmount*) ; 
 int vfs_path_lookup (int /*<<< orphan*/ ,struct vfsmount*,char const*,int,struct path*) ; 

struct dentry *mount_subtree(struct vfsmount *m, const char *name)
{
	struct mount *mnt = real_mount(m);
	struct mnt_namespace *ns;
	struct super_block *s;
	struct path path;
	int err;

	ns = alloc_mnt_ns(&init_user_ns, true);
	if (IS_ERR(ns)) {
		mntput(m);
		return ERR_CAST(ns);
	}
	mnt->mnt_ns = ns;
	ns->root = mnt;
	ns->mounts++;
	list_add(&mnt->mnt_list, &ns->list);

	err = vfs_path_lookup(m->mnt_root, m,
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