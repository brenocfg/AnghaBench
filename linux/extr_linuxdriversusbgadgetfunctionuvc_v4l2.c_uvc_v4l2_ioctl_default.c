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
struct uvc_device {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long ENOIOCTLCMD ; 
#define  UVCIOC_SEND_RESPONSE 128 
 long uvc_send_response (struct uvc_device*,void*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct uvc_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static long
uvc_v4l2_ioctl_default(struct file *file, void *fh, bool valid_prio,
		       unsigned int cmd, void *arg)
{
	struct video_device *vdev = video_devdata(file);
	struct uvc_device *uvc = video_get_drvdata(vdev);

	switch (cmd) {
	case UVCIOC_SEND_RESPONSE:
		return uvc_send_response(uvc, arg);

	default:
		return -ENOIOCTLCMD;
	}
}