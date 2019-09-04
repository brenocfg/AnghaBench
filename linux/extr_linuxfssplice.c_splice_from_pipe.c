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
struct TYPE_2__ {struct file* file; } ;
struct splice_desc {size_t total_len; unsigned int flags; TYPE_1__ u; int /*<<< orphan*/  pos; } ;
struct pipe_inode_info {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  splice_actor ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  __splice_from_pipe (struct pipe_inode_info*,struct splice_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_lock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  pipe_unlock (struct pipe_inode_info*) ; 

ssize_t splice_from_pipe(struct pipe_inode_info *pipe, struct file *out,
			 loff_t *ppos, size_t len, unsigned int flags,
			 splice_actor *actor)
{
	ssize_t ret;
	struct splice_desc sd = {
		.total_len = len,
		.flags = flags,
		.pos = *ppos,
		.u.file = out,
	};

	pipe_lock(pipe);
	ret = __splice_from_pipe(pipe, &sd, actor);
	pipe_unlock(pipe);

	return ret;
}