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
struct uvc_video {int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; } ;
struct uvc_file_handle {int /*<<< orphan*/  vfh; struct uvc_video* device; } ;
struct uvc_device {int dummy; } ;
struct file {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct uvc_file_handle*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct uvc_file_handle* to_uvc_file_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_function_disconnect (struct uvc_device*) ; 
 int /*<<< orphan*/  uvcg_free_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvcg_video_enable (struct uvc_video*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct uvc_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int
uvc_v4l2_release(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	struct uvc_device *uvc = video_get_drvdata(vdev);
	struct uvc_file_handle *handle = to_uvc_file_handle(file->private_data);
	struct uvc_video *video = handle->device;

	uvc_function_disconnect(uvc);

	mutex_lock(&video->mutex);
	uvcg_video_enable(video, 0);
	uvcg_free_buffers(&video->queue);
	mutex_unlock(&video->mutex);

	file->private_data = NULL;
	v4l2_fh_del(&handle->vfh);
	v4l2_fh_exit(&handle->vfh);
	kfree(handle);

	return 0;
}