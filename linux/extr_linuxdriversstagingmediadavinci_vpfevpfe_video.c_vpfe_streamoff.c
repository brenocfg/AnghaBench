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
struct vpfe_video_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer_queue; int /*<<< orphan*/  started; struct vpfe_device* vpfe_dev; } ;
struct vpfe_fh {int /*<<< orphan*/  io_allowed; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct file {struct vpfe_fh* private_data; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  debug ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int vb2_streamoff (int /*<<< orphan*/ *,int) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vpfe_stop_capture (struct vpfe_video_device*) ; 

__attribute__((used)) static int vpfe_streamoff(struct file *file, void *priv,
			  enum v4l2_buf_type buf_type)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	struct vpfe_fh *fh = file->private_data;
	int ret = 0;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_streamoff\n");

	if (buf_type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    buf_type != V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "Invalid buf type\n");
		return -EINVAL;
	}

	/* If io is allowed for this file handle, return error */
	if (!fh->io_allowed) {
		v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "fh->io_allowed\n");
		return -EACCES;
	}

	/* If streaming is not started, return error */
	if (!video->started) {
		v4l2_err(&vpfe_dev->v4l2_dev, "device is not started\n");
		return -EINVAL;
	}

	ret = mutex_lock_interruptible(&video->lock);
	if (ret)
		return ret;

	vpfe_stop_capture(video);
	ret = vb2_streamoff(&video->buffer_queue, buf_type);
	mutex_unlock(&video->lock);

	return ret;
}