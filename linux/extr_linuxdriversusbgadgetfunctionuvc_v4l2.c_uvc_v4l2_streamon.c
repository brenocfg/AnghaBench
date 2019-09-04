#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_device {int dummy; } ;
struct TYPE_3__ {int type; } ;
struct TYPE_4__ {TYPE_1__ queue; } ;
struct uvc_video {TYPE_2__ queue; } ;
struct uvc_device {int /*<<< orphan*/  state; struct uvc_video video; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UVC_STATE_STREAMING ; 
 int /*<<< orphan*/  uvc_function_setup_continue (struct uvc_device*) ; 
 int uvcg_video_enable (struct uvc_video*,int) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct uvc_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int
uvc_v4l2_streamon(struct file *file, void *fh, enum v4l2_buf_type type)
{
	struct video_device *vdev = video_devdata(file);
	struct uvc_device *uvc = video_get_drvdata(vdev);
	struct uvc_video *video = &uvc->video;
	int ret;

	if (type != video->queue.queue.type)
		return -EINVAL;

	/* Enable UVC video. */
	ret = uvcg_video_enable(video, 1);
	if (ret < 0)
		return ret;

	/*
	 * Complete the alternate setting selection setup phase now that
	 * userspace is ready to provide video frames.
	 */
	uvc_function_setup_continue(uvc);
	uvc->state = UVC_STATE_STREAMING;

	return 0;
}