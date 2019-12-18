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
struct file_lock {unsigned char fl_type; int fl_flags; } ;
struct file {int dummy; } ;
struct cifsInodeInfo {int /*<<< orphan*/  lock_sem; int /*<<< orphan*/  can_cache_brlcks; } ;

/* Variables and functions */
 struct cifsInodeInfo* CIFS_I (int /*<<< orphan*/ ) ; 
 int FL_POSIX ; 
 unsigned char F_UNLCK ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  posix_test_lock (struct file*,struct file_lock*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cifs_posix_lock_test(struct file *file, struct file_lock *flock)
{
	int rc = 0;
	struct cifsInodeInfo *cinode = CIFS_I(file_inode(file));
	unsigned char saved_type = flock->fl_type;

	if ((flock->fl_flags & FL_POSIX) == 0)
		return 1;

	down_read(&cinode->lock_sem);
	posix_test_lock(file, flock);

	if (flock->fl_type == F_UNLCK && !cinode->can_cache_brlcks) {
		flock->fl_type = saved_type;
		rc = 1;
	}

	up_read(&cinode->lock_sem);
	return rc;
}