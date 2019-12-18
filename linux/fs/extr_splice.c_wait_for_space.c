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
struct pipe_inode_info {scalar_t__ nrbufs; scalar_t__ buffers; int /*<<< orphan*/  waiting_writers; int /*<<< orphan*/  readers; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EPIPE ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  SIGPIPE ; 
 unsigned int SPLICE_F_NONBLOCK ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  pipe_wait (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int wait_for_space(struct pipe_inode_info *pipe, unsigned flags)
{
	for (;;) {
		if (unlikely(!pipe->readers)) {
			send_sig(SIGPIPE, current, 0);
			return -EPIPE;
		}
		if (pipe->nrbufs != pipe->buffers)
			return 0;
		if (flags & SPLICE_F_NONBLOCK)
			return -EAGAIN;
		if (signal_pending(current))
			return -ERESTARTSYS;
		pipe->waiting_writers++;
		pipe_wait(pipe);
		pipe->waiting_writers--;
	}
}