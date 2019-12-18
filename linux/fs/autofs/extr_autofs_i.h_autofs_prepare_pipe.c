#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {int f_mode; int /*<<< orphan*/  f_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int FMODE_CAN_WRITE ; 
 int /*<<< orphan*/  O_DIRECT ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  S_ISFIFO (int /*<<< orphan*/ ) ; 
 TYPE_1__* file_inode (struct file*) ; 

__attribute__((used)) static inline int autofs_prepare_pipe(struct file *pipe)
{
	if (!(pipe->f_mode & FMODE_CAN_WRITE))
		return -EINVAL;
	if (!S_ISFIFO(file_inode(pipe)->i_mode))
		return -EINVAL;
	/* We want a packet pipe */
	pipe->f_flags |= O_DIRECT;
	/* We don't expect -EAGAIN */
	pipe->f_flags &= ~O_NONBLOCK;
	return 0;
}