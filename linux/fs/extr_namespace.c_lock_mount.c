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
struct vfsmount {int /*<<< orphan*/  mnt_root; } ;
struct path {struct dentry* dentry; struct vfsmount* mnt; } ;
struct mountpoint {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct mountpoint* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct mountpoint*) ; 
 int /*<<< orphan*/  cant_mount (struct dentry*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 struct mountpoint* get_mountpoint (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 struct vfsmount* lookup_mnt (struct path*) ; 
 int /*<<< orphan*/  namespace_lock () ; 
 int /*<<< orphan*/  namespace_unlock () ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mountpoint *lock_mount(struct path *path)
{
	struct vfsmount *mnt;
	struct dentry *dentry = path->dentry;
retry:
	inode_lock(dentry->d_inode);
	if (unlikely(cant_mount(dentry))) {
		inode_unlock(dentry->d_inode);
		return ERR_PTR(-ENOENT);
	}
	namespace_lock();
	mnt = lookup_mnt(path);
	if (likely(!mnt)) {
		struct mountpoint *mp = get_mountpoint(dentry);
		if (IS_ERR(mp)) {
			namespace_unlock();
			inode_unlock(dentry->d_inode);
			return mp;
		}
		return mp;
	}
	namespace_unlock();
	inode_unlock(path->dentry->d_inode);
	path_put(path);
	path->mnt = mnt;
	dentry = path->dentry = dget(mnt->mnt_root);
	goto retry;
}