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
struct file_lock {int fl_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  FL_FLOCK 129 
#define  FL_POSIX 128 
 int flock_lock_inode_wait (struct inode*,struct file_lock*) ; 
 int posix_lock_inode_wait (struct inode*,struct file_lock*) ; 

int locks_lock_inode_wait(struct inode *inode, struct file_lock *fl)
{
	int res = 0;
	switch (fl->fl_flags & (FL_POSIX|FL_FLOCK)) {
		case FL_POSIX:
			res = posix_lock_inode_wait(inode, fl);
			break;
		case FL_FLOCK:
			res = flock_lock_inode_wait(inode, fl);
			break;
		default:
			BUG();
	}
	return res;
}