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
struct pipe_inode_info {int /*<<< orphan*/  fasync_readers; int /*<<< orphan*/  fasync_writers; } ;
struct file {int f_mode; struct pipe_inode_info* private_data; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  __pipe_lock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  __pipe_unlock (struct pipe_inode_info*) ; 
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pipe_fasync(int fd, struct file *filp, int on)
{
	struct pipe_inode_info *pipe = filp->private_data;
	int retval = 0;

	__pipe_lock(pipe);
	if (filp->f_mode & FMODE_READ)
		retval = fasync_helper(fd, filp, on, &pipe->fasync_readers);
	if ((filp->f_mode & FMODE_WRITE) && retval >= 0) {
		retval = fasync_helper(fd, filp, on, &pipe->fasync_writers);
		if (retval < 0 && (filp->f_mode & FMODE_READ))
			/* this can happen only if on == T */
			fasync_helper(-1, filp, 0, &pipe->fasync_readers);
	}
	__pipe_unlock(pipe);
	return retval;
}