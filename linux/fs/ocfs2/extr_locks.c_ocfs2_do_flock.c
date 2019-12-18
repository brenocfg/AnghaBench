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
struct ocfs2_lock_res {int l_flags; scalar_t__ l_level; } ;
struct ocfs2_file_private {int /*<<< orphan*/  fp_mutex; struct ocfs2_lock_res fp_flock; } ;
struct inode {int dummy; } ;
struct file_lock {scalar_t__ fl_type; int /*<<< orphan*/  fl_flags; } ;
struct file {struct ocfs2_file_private* private_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  FL_FLOCK ; 
 scalar_t__ F_UNLCK ; 
 scalar_t__ F_WRLCK ; 
 int /*<<< orphan*/  IS_SETLKW (int) ; 
 scalar_t__ LKM_EXMODE ; 
 scalar_t__ LKM_NLMODE ; 
 int OCFS2_LOCK_ATTACHED ; 
 int /*<<< orphan*/  locks_init_lock (struct file_lock*) ; 
 int locks_lock_file_wait (struct file*,struct file_lock*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocfs2_file_lock (struct file*,int,int) ; 
 int /*<<< orphan*/  ocfs2_file_unlock (struct file*) ; 

__attribute__((used)) static int ocfs2_do_flock(struct file *file, struct inode *inode,
			  int cmd, struct file_lock *fl)
{
	int ret = 0, level = 0, trylock = 0;
	struct ocfs2_file_private *fp = file->private_data;
	struct ocfs2_lock_res *lockres = &fp->fp_flock;

	if (fl->fl_type == F_WRLCK)
		level = 1;
	if (!IS_SETLKW(cmd))
		trylock = 1;

	mutex_lock(&fp->fp_mutex);

	if (lockres->l_flags & OCFS2_LOCK_ATTACHED &&
	    lockres->l_level > LKM_NLMODE) {
		int old_level = 0;
		struct file_lock request;

		if (lockres->l_level == LKM_EXMODE)
			old_level = 1;

		if (level == old_level)
			goto out;

		/*
		 * Converting an existing lock is not guaranteed to be
		 * atomic, so we can get away with simply unlocking
		 * here and allowing the lock code to try at the new
		 * level.
		 */

		locks_init_lock(&request);
		request.fl_type = F_UNLCK;
		request.fl_flags = FL_FLOCK;
		locks_lock_file_wait(file, &request);

		ocfs2_file_unlock(file);
	}

	ret = ocfs2_file_lock(file, level, trylock);
	if (ret) {
		if (ret == -EAGAIN && trylock)
			ret = -EWOULDBLOCK;
		else
			mlog_errno(ret);
		goto out;
	}

	ret = locks_lock_file_wait(file, fl);
	if (ret)
		ocfs2_file_unlock(file);

out:
	mutex_unlock(&fp->fp_mutex);

	return ret;
}