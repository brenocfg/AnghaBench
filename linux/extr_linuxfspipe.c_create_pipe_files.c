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
struct inode {int /*<<< orphan*/  i_pipe; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int ENFILE ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int O_DIRECT ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int PTR_ERR (struct file*) ; 
 struct file* alloc_file_clone (struct file*,int,int /*<<< orphan*/ *) ; 
 struct file* alloc_file_pseudo (struct inode*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  free_pipe_info (int /*<<< orphan*/ ) ; 
 struct inode* get_pipe_inode () ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  pipe_mnt ; 
 int /*<<< orphan*/  pipefifo_fops ; 
 int /*<<< orphan*/  put_pipe_info (struct inode*,int /*<<< orphan*/ ) ; 

int create_pipe_files(struct file **res, int flags)
{
	struct inode *inode = get_pipe_inode();
	struct file *f;

	if (!inode)
		return -ENFILE;

	f = alloc_file_pseudo(inode, pipe_mnt, "",
				O_WRONLY | (flags & (O_NONBLOCK | O_DIRECT)),
				&pipefifo_fops);
	if (IS_ERR(f)) {
		free_pipe_info(inode->i_pipe);
		iput(inode);
		return PTR_ERR(f);
	}

	f->private_data = inode->i_pipe;

	res[0] = alloc_file_clone(f, O_RDONLY | (flags & O_NONBLOCK),
				  &pipefifo_fops);
	if (IS_ERR(res[0])) {
		put_pipe_info(inode, inode->i_pipe);
		fput(f);
		return PTR_ERR(res[0]);
	}
	res[0]->private_data = inode->i_pipe;
	res[1] = f;
	return 0;
}