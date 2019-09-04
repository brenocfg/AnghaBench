#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct video_device {int dummy; } ;
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {TYPE_1__* config; } ;
struct uvc_device {TYPE_2__ func; } ;
struct usb_composite_dev {TYPE_3__* gadget; } ;
struct file {int dummy; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct uvc_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int
uvc_v4l2_querycap(struct file *file, void *fh, struct v4l2_capability *cap)
{
	struct video_device *vdev = video_devdata(file);
	struct uvc_device *uvc = video_get_drvdata(vdev);
	struct usb_composite_dev *cdev = uvc->func.config->cdev;

	strlcpy(cap->driver, "g_uvc", sizeof(cap->driver));
	strlcpy(cap->card, cdev->gadget->name, sizeof(cap->card));
	strlcpy(cap->bus_info, dev_name(&cdev->gadget->dev),
		sizeof(cap->bus_info));

	cap->device_caps = V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_STREAMING;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;

	return 0;
}