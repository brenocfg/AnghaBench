#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec64 {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct path {int /*<<< orphan*/  mnt; TYPE_3__* dentry; } ;
struct inode {int dummy; } ;
struct TYPE_5__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct iattr {int ia_valid; TYPE_2__ ia_mtime; TYPE_1__ ia_atime; } ;
struct TYPE_6__ {struct inode* d_inode; } ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_ATIME_SET ; 
 int ATTR_CTIME ; 
 int ATTR_MTIME ; 
 int ATTR_MTIME_SET ; 
 int ATTR_TIMES_SET ; 
 int ATTR_TOUCH ; 
 scalar_t__ UTIME_NOW ; 
 scalar_t__ UTIME_OMIT ; 
 int break_deleg_wait (struct inode**) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mnt_drop_write (int /*<<< orphan*/ ) ; 
 int mnt_want_write (int /*<<< orphan*/ ) ; 
 int notify_change (TYPE_3__*,struct iattr*,struct inode**) ; 

__attribute__((used)) static int utimes_common(const struct path *path, struct timespec64 *times)
{
	int error;
	struct iattr newattrs;
	struct inode *inode = path->dentry->d_inode;
	struct inode *delegated_inode = NULL;

	error = mnt_want_write(path->mnt);
	if (error)
		goto out;

	if (times && times[0].tv_nsec == UTIME_NOW &&
		     times[1].tv_nsec == UTIME_NOW)
		times = NULL;

	newattrs.ia_valid = ATTR_CTIME | ATTR_MTIME | ATTR_ATIME;
	if (times) {
		if (times[0].tv_nsec == UTIME_OMIT)
			newattrs.ia_valid &= ~ATTR_ATIME;
		else if (times[0].tv_nsec != UTIME_NOW) {
			newattrs.ia_atime.tv_sec = times[0].tv_sec;
			newattrs.ia_atime.tv_nsec = times[0].tv_nsec;
			newattrs.ia_valid |= ATTR_ATIME_SET;
		}

		if (times[1].tv_nsec == UTIME_OMIT)
			newattrs.ia_valid &= ~ATTR_MTIME;
		else if (times[1].tv_nsec != UTIME_NOW) {
			newattrs.ia_mtime.tv_sec = times[1].tv_sec;
			newattrs.ia_mtime.tv_nsec = times[1].tv_nsec;
			newattrs.ia_valid |= ATTR_MTIME_SET;
		}
		/*
		 * Tell setattr_prepare(), that this is an explicit time
		 * update, even if neither ATTR_ATIME_SET nor ATTR_MTIME_SET
		 * were used.
		 */
		newattrs.ia_valid |= ATTR_TIMES_SET;
	} else {
		newattrs.ia_valid |= ATTR_TOUCH;
	}
retry_deleg:
	inode_lock(inode);
	error = notify_change(path->dentry, &newattrs, &delegated_inode);
	inode_unlock(inode);
	if (delegated_inode) {
		error = break_deleg_wait(&delegated_inode);
		if (!error)
			goto retry_deleg;
	}

	mnt_drop_write(path->mnt);
out:
	return error;
}