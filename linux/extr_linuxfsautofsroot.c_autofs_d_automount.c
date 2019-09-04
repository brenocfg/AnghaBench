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
struct path {struct dentry* dentry; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int version; int /*<<< orphan*/  fs_lock; } ;
struct autofs_info {int flags; } ;

/* Variables and functions */
 int AUTOFS_INF_PENDING ; 
 int EAGAIN ; 
 int ENOENT ; 
 struct vfsmount* ERR_PTR (int) ; 
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 int autofs_mount_wait (struct path*,int /*<<< orphan*/ ) ; 
 struct dentry* autofs_mountpoint_changed (struct path*) ; 
 scalar_t__ autofs_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 scalar_t__ d_is_symlink (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int do_expire_wait (struct path*,int /*<<< orphan*/ ) ; 
 scalar_t__ path_has_submounts (struct path*) ; 
 int /*<<< orphan*/  path_is_mountpoint (struct path*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  simple_empty (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vfsmount *autofs_d_automount(struct path *path)
{
	struct dentry *dentry = path->dentry;
	struct autofs_sb_info *sbi = autofs_sbi(dentry->d_sb);
	struct autofs_info *ino = autofs_dentry_ino(dentry);
	int status;

	pr_debug("dentry=%p %pd\n", dentry, dentry);

	/* The daemon never triggers a mount. */
	if (autofs_oz_mode(sbi))
		return NULL;

	/*
	 * If an expire request is pending everyone must wait.
	 * If the expire fails we're still mounted so continue
	 * the follow and return. A return of -EAGAIN (which only
	 * happens with indirect mounts) means the expire completed
	 * and the directory was removed, so just go ahead and try
	 * the mount.
	 */
	status = do_expire_wait(path, 0);
	if (status && status != -EAGAIN)
		return NULL;

	/* Callback to the daemon to perform the mount or wait */
	spin_lock(&sbi->fs_lock);
	if (ino->flags & AUTOFS_INF_PENDING) {
		spin_unlock(&sbi->fs_lock);
		status = autofs_mount_wait(path, 0);
		if (status)
			return ERR_PTR(status);
		goto done;
	}

	/*
	 * If the dentry is a symlink it's equivalent to a directory
	 * having path_is_mountpoint() true, so there's no need to call
	 * back to the daemon.
	 */
	if (d_really_is_positive(dentry) && d_is_symlink(dentry)) {
		spin_unlock(&sbi->fs_lock);
		goto done;
	}

	if (!path_is_mountpoint(path)) {
		/*
		 * It's possible that user space hasn't removed directories
		 * after umounting a rootless multi-mount, although it
		 * should. For v5 path_has_submounts() is sufficient to
		 * handle this because the leaves of the directory tree under
		 * the mount never trigger mounts themselves (they have an
		 * autofs trigger mount mounted on them). But v4 pseudo direct
		 * mounts do need the leaves to trigger mounts. In this case
		 * we have no choice but to use the list_empty() check and
		 * require user space behave.
		 */
		if (sbi->version > 4) {
			if (path_has_submounts(path)) {
				spin_unlock(&sbi->fs_lock);
				goto done;
			}
		} else {
			if (!simple_empty(dentry)) {
				spin_unlock(&sbi->fs_lock);
				goto done;
			}
		}
		ino->flags |= AUTOFS_INF_PENDING;
		spin_unlock(&sbi->fs_lock);
		status = autofs_mount_wait(path, 0);
		spin_lock(&sbi->fs_lock);
		ino->flags &= ~AUTOFS_INF_PENDING;
		if (status) {
			spin_unlock(&sbi->fs_lock);
			return ERR_PTR(status);
		}
	}
	spin_unlock(&sbi->fs_lock);
done:
	/* Mount succeeded, check if we ended up with a new dentry */
	dentry = autofs_mountpoint_changed(path);
	if (!dentry)
		return ERR_PTR(-ENOENT);

	return NULL;
}