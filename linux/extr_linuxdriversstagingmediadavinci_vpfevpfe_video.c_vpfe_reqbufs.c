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
struct vb2_queue {scalar_t__ type; int io_modes; int min_buffers_needed; int buf_struct_size; int /*<<< orphan*/ * lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct vpfe_fh* drv_priv; } ;
struct vpfe_video_device {int io_usrs; int /*<<< orphan*/  lock; struct vb2_queue buffer_queue; int /*<<< orphan*/  dma_queue; int /*<<< orphan*/  memory; struct vpfe_device* vpfe_dev; } ;
struct vpfe_fh {int io_allowed; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  pdev; } ;
struct vpfe_cap_buffer {int dummy; } ;
struct v4l2_requestbuffers {scalar_t__ type; int /*<<< orphan*/  memory; } ;
struct file {struct vpfe_fh* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int VB2_MMAP ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  debug ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 
 int vb2_reqbufs (struct vb2_queue*,struct v4l2_requestbuffers*) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  video_qops ; 

__attribute__((used)) static int vpfe_reqbufs(struct file *file, void *priv,
			struct v4l2_requestbuffers *req_buf)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	struct vpfe_fh *fh = file->private_data;
	struct vb2_queue *q;
	int ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_reqbufs\n");

	if (req_buf->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    req_buf->type != V4L2_BUF_TYPE_VIDEO_OUTPUT){
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid buffer type\n");
		return -EINVAL;
	}

	ret = mutex_lock_interruptible(&video->lock);
	if (ret)
		return ret;

	if (video->io_usrs != 0) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Only one IO user allowed\n");
		ret = -EBUSY;
		goto unlock_out;
	}
	video->memory = req_buf->memory;

	/* Initialize videobuf2 queue as per the buffer type */
	q = &video->buffer_queue;
	q->type = req_buf->type;
	q->io_modes = VB2_MMAP | VB2_USERPTR;
	q->drv_priv = fh;
	q->min_buffers_needed = 1;
	q->ops = &video_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_struct_size = sizeof(struct vpfe_cap_buffer);
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->dev = vpfe_dev->pdev;
	q->lock = &video->lock;

	ret = vb2_queue_init(q);
	if (ret) {
		v4l2_err(&vpfe_dev->v4l2_dev, "vb2_queue_init() failed\n");
		goto unlock_out;
	}

	fh->io_allowed = 1;
	video->io_usrs = 1;
	INIT_LIST_HEAD(&video->dma_queue);
	ret = vb2_reqbufs(&video->buffer_queue, req_buf);

unlock_out:
	mutex_unlock(&video->lock);
	return ret;
}