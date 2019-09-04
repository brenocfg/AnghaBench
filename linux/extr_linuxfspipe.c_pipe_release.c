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
struct pipe_inode_info {int /*<<< orphan*/  fasync_writers; int /*<<< orphan*/  fasync_readers; int /*<<< orphan*/  wait; scalar_t__ writers; scalar_t__ readers; } ;
struct inode {int dummy; } ;
struct file {int f_mode; struct pipe_inode_info* private_data; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  POLL_OUT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  __pipe_lock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  __pipe_unlock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pipe_info (struct inode*,struct pipe_inode_info*) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync_poll (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
pipe_release(struct inode *inode, struct file *file)
{
	struct pipe_inode_info *pipe = file->private_data;

	__pipe_lock(pipe);
	if (file->f_mode & FMODE_READ)
		pipe->readers--;
	if (file->f_mode & FMODE_WRITE)
		pipe->writers--;

	if (pipe->readers || pipe->writers) {
		wake_up_interruptible_sync_poll(&pipe->wait, EPOLLIN | EPOLLOUT | EPOLLRDNORM | EPOLLWRNORM | EPOLLERR | EPOLLHUP);
		kill_fasync(&pipe->fasync_readers, SIGIO, POLL_IN);
		kill_fasync(&pipe->fasync_writers, SIGIO, POLL_OUT);
	}
	__pipe_unlock(pipe);

	put_pipe_info(inode, pipe);
	return 0;
}