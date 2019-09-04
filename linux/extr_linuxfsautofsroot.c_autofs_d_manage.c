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
struct path {struct dentry* dentry; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {int /*<<< orphan*/  d_subdirs; int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int /*<<< orphan*/  fs_lock; } ;
struct autofs_info {int flags; } ;

/* Variables and functions */
 int AUTOFS_INF_EXPIRING ; 
 int AUTOFS_INF_WANT_EXPIRE ; 
 int ECHILD ; 
 int EISDIR ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 int autofs_mount_wait (struct path const*,int) ; 
 scalar_t__ autofs_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 struct inode* d_inode_rcu (struct dentry*) ; 
 scalar_t__ d_is_symlink (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int do_expire_wait (struct path const*,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ path_is_mountpoint (struct path const*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  simple_empty (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int autofs_d_manage(const struct path *path, bool rcu_walk)
{
	struct dentry *dentry = path->dentry;
	struct autofs_sb_info *sbi = autofs_sbi(dentry->d_sb);
	struct autofs_info *ino = autofs_dentry_ino(dentry);
	int status;

	pr_debug("dentry=%p %pd\n", dentry, dentry);

	/* The daemon never waits. */
	if (autofs_oz_mode(sbi)) {
		if (!path_is_mountpoint(path))
			return -EISDIR;
		return 0;
	}

	/* Wait for pending expires */
	if (do_expire_wait(path, rcu_walk) == -ECHILD)
		return -ECHILD;

	/*
	 * This dentry may be under construction so wait on mount
	 * completion.
	 */
	status = autofs_mount_wait(path, rcu_walk);
	if (status)
		return status;

	if (rcu_walk) {
		/* We don't need fs_lock in rcu_walk mode,
		 * just testing 'AUTOFS_INFO_NO_RCU' is enough.
		 * simple_empty() takes a spinlock, so leave it
		 * to last.
		 * We only return -EISDIR when certain this isn't
		 * a mount-trap.
		 */
		struct inode *inode;

		if (ino->flags & AUTOFS_INF_WANT_EXPIRE)
			return 0;
		if (path_is_mountpoint(path))
			return 0;
		inode = d_inode_rcu(dentry);
		if (inode && S_ISLNK(inode->i_mode))
			return -EISDIR;
		if (list_empty(&dentry->d_subdirs))
			return 0;
		if (!simple_empty(dentry))
			return -EISDIR;
		return 0;
	}

	spin_lock(&sbi->fs_lock);
	/*
	 * If the dentry has been selected for expire while we slept
	 * on the lock then it might go away. We'll deal with that in
	 * ->d_automount() and wait on a new mount if the expire
	 * succeeds or return here if it doesn't (since there's no
	 * mount to follow with a rootless multi-mount).
	 */
	if (!(ino->flags & AUTOFS_INF_EXPIRING)) {
		/*
		 * Any needed mounting has been completed and the path
		 * updated so check if this is a rootless multi-mount so
		 * we can avoid needless calls ->d_automount() and avoid
		 * an incorrect ELOOP error return.
		 */
		if ((!path_is_mountpoint(path) && !simple_empty(dentry)) ||
		    (d_really_is_positive(dentry) && d_is_symlink(dentry)))
			status = -EISDIR;
	}
	spin_unlock(&sbi->fs_lock);

	return status;
}