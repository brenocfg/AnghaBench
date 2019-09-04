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
struct video_device {int dummy; } ;
struct v4l2_buffer {int dummy; } ;
struct uvc_video {int /*<<< orphan*/  queue; } ;
struct uvc_device {struct uvc_video video; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int uvcg_dequeue_buffer (int /*<<< orphan*/ *,struct v4l2_buffer*,int) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct uvc_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int
uvc_v4l2_dqbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
	struct video_device *vdev = video_devdata(file);
	struct uvc_device *uvc = video_get_drvdata(vdev);
	struct uvc_video *video = &uvc->video;

	return uvcg_dequeue_buffer(&video->queue, b, file->f_flags & O_NONBLOCK);
}