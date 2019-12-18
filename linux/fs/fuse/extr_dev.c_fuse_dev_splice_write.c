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
struct pipe_inode_info {unsigned int nrbufs; unsigned int curbuf; int buffers; struct pipe_buffer* bufs; } ;
struct pipe_buffer {size_t len; size_t offset; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;
struct fuse_dev {int dummy; } ;
struct fuse_copy_state {unsigned int nr_segs; int move_pages; struct pipe_inode_info* pipe; struct pipe_buffer* pipebufs; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PIPE_BUF_FLAG_GIFT ; 
 unsigned int SPLICE_F_MOVE ; 
 int /*<<< orphan*/  fuse_copy_init (struct fuse_copy_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_dev_do_write (struct fuse_dev*,struct fuse_copy_state*,size_t) ; 
 struct fuse_dev* fuse_get_dev (struct file*) ; 
 int /*<<< orphan*/  kvfree (struct pipe_buffer*) ; 
 struct pipe_buffer* kvmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_buf_get (struct pipe_inode_info*,struct pipe_buffer*) ; 
 int /*<<< orphan*/  pipe_buf_release (struct pipe_inode_info*,struct pipe_buffer*) ; 
 int /*<<< orphan*/  pipe_lock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  pipe_unlock (struct pipe_inode_info*) ; 

__attribute__((used)) static ssize_t fuse_dev_splice_write(struct pipe_inode_info *pipe,
				     struct file *out, loff_t *ppos,
				     size_t len, unsigned int flags)
{
	unsigned nbuf;
	unsigned idx;
	struct pipe_buffer *bufs;
	struct fuse_copy_state cs;
	struct fuse_dev *fud;
	size_t rem;
	ssize_t ret;

	fud = fuse_get_dev(out);
	if (!fud)
		return -EPERM;

	pipe_lock(pipe);

	bufs = kvmalloc_array(pipe->nrbufs, sizeof(struct pipe_buffer),
			      GFP_KERNEL);
	if (!bufs) {
		pipe_unlock(pipe);
		return -ENOMEM;
	}

	nbuf = 0;
	rem = 0;
	for (idx = 0; idx < pipe->nrbufs && rem < len; idx++)
		rem += pipe->bufs[(pipe->curbuf + idx) & (pipe->buffers - 1)].len;

	ret = -EINVAL;
	if (rem < len)
		goto out_free;

	rem = len;
	while (rem) {
		struct pipe_buffer *ibuf;
		struct pipe_buffer *obuf;

		BUG_ON(nbuf >= pipe->buffers);
		BUG_ON(!pipe->nrbufs);
		ibuf = &pipe->bufs[pipe->curbuf];
		obuf = &bufs[nbuf];

		if (rem >= ibuf->len) {
			*obuf = *ibuf;
			ibuf->ops = NULL;
			pipe->curbuf = (pipe->curbuf + 1) & (pipe->buffers - 1);
			pipe->nrbufs--;
		} else {
			if (!pipe_buf_get(pipe, ibuf))
				goto out_free;

			*obuf = *ibuf;
			obuf->flags &= ~PIPE_BUF_FLAG_GIFT;
			obuf->len = rem;
			ibuf->offset += obuf->len;
			ibuf->len -= obuf->len;
		}
		nbuf++;
		rem -= obuf->len;
	}
	pipe_unlock(pipe);

	fuse_copy_init(&cs, 0, NULL);
	cs.pipebufs = bufs;
	cs.nr_segs = nbuf;
	cs.pipe = pipe;

	if (flags & SPLICE_F_MOVE)
		cs.move_pages = 1;

	ret = fuse_dev_do_write(fud, &cs, len);

	pipe_lock(pipe);
out_free:
	for (idx = 0; idx < nbuf; idx++)
		pipe_buf_release(pipe, &bufs[idx]);
	pipe_unlock(pipe);

	kvfree(bufs);
	return ret;
}