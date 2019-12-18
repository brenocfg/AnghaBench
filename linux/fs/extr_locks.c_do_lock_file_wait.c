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
struct file_lock {int /*<<< orphan*/  fl_blocker; int /*<<< orphan*/  fl_wait; int /*<<< orphan*/  fl_type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int FILE_LOCK_DEFERRED ; 
 int /*<<< orphan*/  locks_delete_block (struct file_lock*) ; 
 int security_file_lock (struct file*,int /*<<< orphan*/ ) ; 
 int vfs_lock_file (struct file*,unsigned int,struct file_lock*,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_lock_file_wait(struct file *filp, unsigned int cmd,
			     struct file_lock *fl)
{
	int error;

	error = security_file_lock(filp, fl->fl_type);
	if (error)
		return error;

	for (;;) {
		error = vfs_lock_file(filp, cmd, fl, NULL);
		if (error != FILE_LOCK_DEFERRED)
			break;
		error = wait_event_interruptible(fl->fl_wait, !fl->fl_blocker);
		if (error)
			break;
	}
	locks_delete_block(fl);

	return error;
}