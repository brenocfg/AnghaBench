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
struct pipe_inode_info {int nrbufs; int buffers; int curbuf; struct pipe_buffer* bufs; int /*<<< orphan*/  readers; } ;
struct pipe_buffer {int len; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EPIPE ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  pipe_buf_release (struct pipe_inode_info*,struct pipe_buffer*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

ssize_t add_to_pipe(struct pipe_inode_info *pipe, struct pipe_buffer *buf)
{
	int ret;

	if (unlikely(!pipe->readers)) {
		send_sig(SIGPIPE, current, 0);
		ret = -EPIPE;
	} else if (pipe->nrbufs == pipe->buffers) {
		ret = -EAGAIN;
	} else {
		int newbuf = (pipe->curbuf + pipe->nrbufs) & (pipe->buffers - 1);
		pipe->bufs[newbuf] = *buf;
		pipe->nrbufs++;
		return buf->len;
	}
	pipe_buf_release(pipe, buf);
	return ret;
}