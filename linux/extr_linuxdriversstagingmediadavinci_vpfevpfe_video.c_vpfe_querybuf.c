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
struct vpfe_video_device {scalar_t__ memory; int /*<<< orphan*/  buffer_queue; struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_buffer {scalar_t__ type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int vb2_querybuf (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpfe_querybuf(struct file *file, void *priv,
			 struct v4l2_buffer *buf)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_device *vpfe_dev = video->vpfe_dev;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_querybuf\n");

	if (buf->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    buf->type != V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid buf type\n");
		return  -EINVAL;
	}

	if (video->memory != V4L2_MEMORY_MMAP) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid memory\n");
		return -EINVAL;
	}

	/* Call vb2_querybuf to get information */
	return vb2_querybuf(&video->buffer_queue, buf);
}