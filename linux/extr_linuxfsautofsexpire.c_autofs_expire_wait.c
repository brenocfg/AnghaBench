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
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int /*<<< orphan*/  fs_lock; } ;
struct autofs_info {int flags; int /*<<< orphan*/  expire_complete; } ;

/* Variables and functions */
 int AUTOFS_INF_EXPIRING ; 
 int AUTOFS_INF_WANT_EXPIRE ; 
 int EAGAIN ; 
 int ECHILD ; 
 int HZ ; 
 int /*<<< orphan*/  NFY_NONE ; 
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int autofs_wait (struct autofs_sb_info*,struct path const*,int /*<<< orphan*/ ) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int autofs_expire_wait(const struct path *path, int rcu_walk)
{
	struct dentry *dentry = path->dentry;
	struct autofs_sb_info *sbi = autofs_sbi(dentry->d_sb);
	struct autofs_info *ino = autofs_dentry_ino(dentry);
	int status;
	int state;

	/* Block on any pending expire */
	if (!(ino->flags & AUTOFS_INF_WANT_EXPIRE))
		return 0;
	if (rcu_walk)
		return -ECHILD;

retry:
	spin_lock(&sbi->fs_lock);
	state = ino->flags & (AUTOFS_INF_WANT_EXPIRE | AUTOFS_INF_EXPIRING);
	if (state == AUTOFS_INF_WANT_EXPIRE) {
		spin_unlock(&sbi->fs_lock);
		/*
		 * Possibly being selected for expire, wait until
		 * it's selected or not.
		 */
		schedule_timeout_uninterruptible(HZ/10);
		goto retry;
	}
	if (state & AUTOFS_INF_EXPIRING) {
		spin_unlock(&sbi->fs_lock);

		pr_debug("waiting for expire %p name=%pd\n", dentry, dentry);

		status = autofs_wait(sbi, path, NFY_NONE);
		wait_for_completion(&ino->expire_complete);

		pr_debug("expire done status=%d\n", status);

		if (d_unhashed(dentry))
			return -EAGAIN;

		return status;
	}
	spin_unlock(&sbi->fs_lock);

	return 0;
}