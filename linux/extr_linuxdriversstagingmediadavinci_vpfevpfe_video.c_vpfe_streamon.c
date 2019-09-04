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
struct TYPE_2__ {int /*<<< orphan*/  queued_list; } ;
struct vpfe_pipeline {int dummy; } ;
struct vpfe_video_device {TYPE_1__ buffer_queue; struct vpfe_pipeline pipe; struct vpfe_device* vpfe_dev; } ;
struct vpfe_fh {int /*<<< orphan*/  io_allowed; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct file {struct vpfe_fh* private_data; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int vb2_streamon (TYPE_1__*,int) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 
 int vpfe_video_validate_pipeline (struct vpfe_pipeline*) ; 

__attribute__((used)) static int vpfe_streamon(struct file *file, void *priv,
			 enum v4l2_buf_type buf_type)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	struct vpfe_pipeline *pipe = &video->pipe;
	struct vpfe_fh *fh = file->private_data;
	int ret = -EINVAL;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_streamon\n");

	if (buf_type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    buf_type != V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid buf type\n");
		return ret;
	}
	/* If file handle is not allowed IO, return error */
	if (!fh->io_allowed) {
		v4l2_err(&vpfe_dev->v4l2_dev, "fh->io_allowed\n");
		return -EACCES;
	}
	/* If buffer queue is empty, return error */
	if (list_empty(&video->buffer_queue.queued_list)) {
		v4l2_err(&vpfe_dev->v4l2_dev, "buffer queue is empty\n");
		return -EIO;
	}
	/* Validate the pipeline */
	if (buf_type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		ret = vpfe_video_validate_pipeline(pipe);
		if (ret < 0)
			return ret;
	}
	/* Call vb2_streamon to start streaming */
	return vb2_streamon(&video->buffer_queue, buf_type);
}