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
struct pipe_inode_info {unsigned int buffers; unsigned int nrbufs; unsigned int curbuf; int /*<<< orphan*/  user; struct pipe_buffer* bufs; } ;
struct pipe_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 long EBUSY ; 
 long EINVAL ; 
 long ENOMEM ; 
 long EPERM ; 
 int GFP_KERNEL_ACCOUNT ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int __GFP_NOWARN ; 
 unsigned long account_pipe_buffers (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ is_unprivileged_user () ; 
 struct pipe_buffer* kcalloc (unsigned int,int,int) ; 
 int /*<<< orphan*/  kfree (struct pipe_buffer*) ; 
 int /*<<< orphan*/  memcpy (struct pipe_buffer*,struct pipe_buffer*,unsigned int) ; 
 unsigned int pipe_max_size ; 
 unsigned int round_pipe_size (unsigned long) ; 
 scalar_t__ too_many_pipe_buffers_hard (unsigned long) ; 
 scalar_t__ too_many_pipe_buffers_soft (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static long pipe_set_size(struct pipe_inode_info *pipe, unsigned long arg)
{
	struct pipe_buffer *bufs;
	unsigned int size, nr_pages;
	unsigned long user_bufs;
	long ret = 0;

	size = round_pipe_size(arg);
	nr_pages = size >> PAGE_SHIFT;

	if (!nr_pages)
		return -EINVAL;

	/*
	 * If trying to increase the pipe capacity, check that an
	 * unprivileged user is not trying to exceed various limits
	 * (soft limit check here, hard limit check just below).
	 * Decreasing the pipe capacity is always permitted, even
	 * if the user is currently over a limit.
	 */
	if (nr_pages > pipe->buffers &&
			size > pipe_max_size && !capable(CAP_SYS_RESOURCE))
		return -EPERM;

	user_bufs = account_pipe_buffers(pipe->user, pipe->buffers, nr_pages);

	if (nr_pages > pipe->buffers &&
			(too_many_pipe_buffers_hard(user_bufs) ||
			 too_many_pipe_buffers_soft(user_bufs)) &&
			is_unprivileged_user()) {
		ret = -EPERM;
		goto out_revert_acct;
	}

	/*
	 * We can shrink the pipe, if arg >= pipe->nrbufs. Since we don't
	 * expect a lot of shrink+grow operations, just free and allocate
	 * again like we would do for growing. If the pipe currently
	 * contains more buffers than arg, then return busy.
	 */
	if (nr_pages < pipe->nrbufs) {
		ret = -EBUSY;
		goto out_revert_acct;
	}

	bufs = kcalloc(nr_pages, sizeof(*bufs),
		       GFP_KERNEL_ACCOUNT | __GFP_NOWARN);
	if (unlikely(!bufs)) {
		ret = -ENOMEM;
		goto out_revert_acct;
	}

	/*
	 * The pipe array wraps around, so just start the new one at zero
	 * and adjust the indexes.
	 */
	if (pipe->nrbufs) {
		unsigned int tail;
		unsigned int head;

		tail = pipe->curbuf + pipe->nrbufs;
		if (tail < pipe->buffers)
			tail = 0;
		else
			tail &= (pipe->buffers - 1);

		head = pipe->nrbufs - tail;
		if (head)
			memcpy(bufs, pipe->bufs + pipe->curbuf, head * sizeof(struct pipe_buffer));
		if (tail)
			memcpy(bufs + head, pipe->bufs, tail * sizeof(struct pipe_buffer));
	}

	pipe->curbuf = 0;
	kfree(pipe->bufs);
	pipe->bufs = bufs;
	pipe->buffers = nr_pages;
	return nr_pages * PAGE_SIZE;

out_revert_acct:
	(void) account_pipe_buffers(pipe->user, nr_pages, pipe->buffers);
	return ret;
}