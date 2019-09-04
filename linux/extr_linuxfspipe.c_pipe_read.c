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
struct pipe_inode_info {int nrbufs; int curbuf; int buffers; int /*<<< orphan*/  fasync_writers; int /*<<< orphan*/  wait; int /*<<< orphan*/  waiting_writers; int /*<<< orphan*/  writers; struct pipe_buffer* bufs; } ;
struct pipe_buffer {size_t len; size_t offset; int flags; int /*<<< orphan*/  page; } ;
struct kiocb {struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct file {int f_flags; struct pipe_inode_info* private_data; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EAGAIN ; 
 size_t EFAULT ; 
 int EPOLLOUT ; 
 int EPOLLWRNORM ; 
 size_t ERESTARTSYS ; 
 int O_NONBLOCK ; 
 int PIPE_BUF_FLAG_PACKET ; 
 int /*<<< orphan*/  POLL_OUT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  __pipe_lock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  __pipe_unlock (struct pipe_inode_info*) ; 
 size_t copy_page_to_iter (int /*<<< orphan*/ ,size_t,size_t,struct iov_iter*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pipe_buf_confirm (struct pipe_inode_info*,struct pipe_buffer*) ; 
 int /*<<< orphan*/  pipe_buf_release (struct pipe_inode_info*,struct pipe_buffer*) ; 
 int /*<<< orphan*/  pipe_wait (struct pipe_inode_info*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync_poll (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t
pipe_read(struct kiocb *iocb, struct iov_iter *to)
{
	size_t total_len = iov_iter_count(to);
	struct file *filp = iocb->ki_filp;
	struct pipe_inode_info *pipe = filp->private_data;
	int do_wakeup;
	ssize_t ret;

	/* Null read succeeds. */
	if (unlikely(total_len == 0))
		return 0;

	do_wakeup = 0;
	ret = 0;
	__pipe_lock(pipe);
	for (;;) {
		int bufs = pipe->nrbufs;
		if (bufs) {
			int curbuf = pipe->curbuf;
			struct pipe_buffer *buf = pipe->bufs + curbuf;
			size_t chars = buf->len;
			size_t written;
			int error;

			if (chars > total_len)
				chars = total_len;

			error = pipe_buf_confirm(pipe, buf);
			if (error) {
				if (!ret)
					ret = error;
				break;
			}

			written = copy_page_to_iter(buf->page, buf->offset, chars, to);
			if (unlikely(written < chars)) {
				if (!ret)
					ret = -EFAULT;
				break;
			}
			ret += chars;
			buf->offset += chars;
			buf->len -= chars;

			/* Was it a packet buffer? Clean up and exit */
			if (buf->flags & PIPE_BUF_FLAG_PACKET) {
				total_len = chars;
				buf->len = 0;
			}

			if (!buf->len) {
				pipe_buf_release(pipe, buf);
				curbuf = (curbuf + 1) & (pipe->buffers - 1);
				pipe->curbuf = curbuf;
				pipe->nrbufs = --bufs;
				do_wakeup = 1;
			}
			total_len -= chars;
			if (!total_len)
				break;	/* common path: read succeeded */
		}
		if (bufs)	/* More to do? */
			continue;
		if (!pipe->writers)
			break;
		if (!pipe->waiting_writers) {
			/* syscall merging: Usually we must not sleep
			 * if O_NONBLOCK is set, or if we got some data.
			 * But if a writer sleeps in kernel space, then
			 * we can wait for that data without violating POSIX.
			 */
			if (ret)
				break;
			if (filp->f_flags & O_NONBLOCK) {
				ret = -EAGAIN;
				break;
			}
		}
		if (signal_pending(current)) {
			if (!ret)
				ret = -ERESTARTSYS;
			break;
		}
		if (do_wakeup) {
			wake_up_interruptible_sync_poll(&pipe->wait, EPOLLOUT | EPOLLWRNORM);
 			kill_fasync(&pipe->fasync_writers, SIGIO, POLL_OUT);
		}
		pipe_wait(pipe);
	}
	__pipe_unlock(pipe);

	/* Signal writers asynchronously that there is more room. */
	if (do_wakeup) {
		wake_up_interruptible_sync_poll(&pipe->wait, EPOLLOUT | EPOLLWRNORM);
		kill_fasync(&pipe->fasync_writers, SIGIO, POLL_OUT);
	}
	if (ret > 0)
		file_accessed(filp);
	return ret;
}