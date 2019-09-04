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
struct video_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct uvc_device {TYPE_1__ video; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  uvcg_queue_poll (int /*<<< orphan*/ *,struct file*,int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct uvc_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static __poll_t
uvc_v4l2_poll(struct file *file, poll_table *wait)
{
	struct video_device *vdev = video_devdata(file);
	struct uvc_device *uvc = video_get_drvdata(vdev);

	return uvcg_queue_poll(&uvc->video.queue, file, wait);
}