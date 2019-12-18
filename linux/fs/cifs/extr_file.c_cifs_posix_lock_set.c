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
struct file_lock {int fl_flags; int /*<<< orphan*/  fl_blocker; int /*<<< orphan*/  fl_wait; } ;
struct file {int dummy; } ;
struct cifsInodeInfo {int /*<<< orphan*/  lock_sem; int /*<<< orphan*/  can_cache_brlcks; } ;

/* Variables and functions */
 struct cifsInodeInfo* CIFS_I (int /*<<< orphan*/ ) ; 
 int FILE_LOCK_DEFERRED ; 
 int FL_POSIX ; 
 int /*<<< orphan*/  cifs_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  locks_delete_block (struct file_lock*) ; 
 int posix_lock_file (struct file*,struct file_lock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cifs_posix_lock_set(struct file *file, struct file_lock *flock)
{
	struct cifsInodeInfo *cinode = CIFS_I(file_inode(file));
	int rc = 1;

	if ((flock->fl_flags & FL_POSIX) == 0)
		return rc;

try_again:
	cifs_down_write(&cinode->lock_sem);
	if (!cinode->can_cache_brlcks) {
		up_write(&cinode->lock_sem);
		return rc;
	}

	rc = posix_lock_file(file, flock, NULL);
	up_write(&cinode->lock_sem);
	if (rc == FILE_LOCK_DEFERRED) {
		rc = wait_event_interruptible(flock->fl_wait, !flock->fl_blocker);
		if (!rc)
			goto try_again;
		locks_delete_block(flock);
	}
	return rc;
}