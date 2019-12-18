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
struct inode {int dummy; } ;
struct file_lock {int /*<<< orphan*/  fl_blocker; int /*<<< orphan*/  fl_wait; } ;

/* Variables and functions */
 int FILE_LOCK_DEFERRED ; 
 int /*<<< orphan*/  locks_delete_block (struct file_lock*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int posix_lock_inode (struct inode*,struct file_lock*,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int posix_lock_inode_wait(struct inode *inode, struct file_lock *fl)
{
	int error;
	might_sleep ();
	for (;;) {
		error = posix_lock_inode(inode, fl, NULL);
		if (error != FILE_LOCK_DEFERRED)
			break;
		error = wait_event_interruptible(fl->fl_wait, !fl->fl_blocker);
		if (error)
			break;
	}
	locks_delete_block(fl);
	return error;
}