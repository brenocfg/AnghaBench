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
struct pipe_inode_info {long buffers; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long EBADF ; 
 long EINVAL ; 
#define  F_GETPIPE_SZ 129 
#define  F_SETPIPE_SZ 128 
 long PAGE_SIZE ; 
 int /*<<< orphan*/  __pipe_lock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  __pipe_unlock (struct pipe_inode_info*) ; 
 struct pipe_inode_info* get_pipe_info (struct file*) ; 
 long pipe_set_size (struct pipe_inode_info*,unsigned long) ; 

long pipe_fcntl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct pipe_inode_info *pipe;
	long ret;

	pipe = get_pipe_info(file);
	if (!pipe)
		return -EBADF;

	__pipe_lock(pipe);

	switch (cmd) {
	case F_SETPIPE_SZ:
		ret = pipe_set_size(pipe, arg);
		break;
	case F_GETPIPE_SZ:
		ret = pipe->buffers * PAGE_SIZE;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	__pipe_unlock(pipe);
	return ret;
}