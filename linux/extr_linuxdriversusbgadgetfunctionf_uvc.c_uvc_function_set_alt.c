#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v4l2_event ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct v4l2_event {int /*<<< orphan*/  type; TYPE_1__ u; } ;
struct uvc_event {int /*<<< orphan*/  speed; } ;
struct TYPE_10__ {TYPE_4__* ep; } ;
struct usb_function {TYPE_2__* config; } ;
struct uvc_device {unsigned int control_intf; scalar_t__ state; unsigned int streaming_intf; int /*<<< orphan*/  vdev; TYPE_3__ video; struct usb_function func; TYPE_4__* control_ep; } ;
struct usb_composite_dev {TYPE_6__* gadget; } ;
struct TYPE_12__ {int /*<<< orphan*/  speed; } ;
struct TYPE_11__ {int /*<<< orphan*/  desc; } ;
struct TYPE_9__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INFO (struct usb_composite_dev*,char*,...) ; 
 int USB_GADGET_DELAYED_STATUS ; 
 int /*<<< orphan*/  UVC_EVENT_CONNECT ; 
 int /*<<< orphan*/  UVC_EVENT_STREAMOFF ; 
 int /*<<< orphan*/  UVC_EVENT_STREAMON ; 
 scalar_t__ UVC_STATE_CONNECTED ; 
 scalar_t__ UVC_STATE_DISCONNECTED ; 
 scalar_t__ UVC_STATE_STREAMING ; 
 int config_ep_by_speed (TYPE_6__*,struct usb_function*,TYPE_4__*) ; 
 int /*<<< orphan*/  memset (struct v4l2_event*,int /*<<< orphan*/ ,int) ; 
 struct uvc_device* to_uvc (struct usb_function*) ; 
 int /*<<< orphan*/  usb_ep_disable (TYPE_4__*) ; 
 int /*<<< orphan*/  usb_ep_enable (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_event_queue (int /*<<< orphan*/ *,struct v4l2_event*) ; 

__attribute__((used)) static int
uvc_function_set_alt(struct usb_function *f, unsigned interface, unsigned alt)
{
	struct uvc_device *uvc = to_uvc(f);
	struct usb_composite_dev *cdev = f->config->cdev;
	struct v4l2_event v4l2_event;
	struct uvc_event *uvc_event = (void *)&v4l2_event.u.data;
	int ret;

	INFO(cdev, "uvc_function_set_alt(%u, %u)\n", interface, alt);

	if (interface == uvc->control_intf) {
		if (alt)
			return -EINVAL;

		INFO(cdev, "reset UVC Control\n");
		usb_ep_disable(uvc->control_ep);

		if (!uvc->control_ep->desc)
			if (config_ep_by_speed(cdev->gadget, f, uvc->control_ep))
				return -EINVAL;

		usb_ep_enable(uvc->control_ep);

		if (uvc->state == UVC_STATE_DISCONNECTED) {
			memset(&v4l2_event, 0, sizeof(v4l2_event));
			v4l2_event.type = UVC_EVENT_CONNECT;
			uvc_event->speed = cdev->gadget->speed;
			v4l2_event_queue(&uvc->vdev, &v4l2_event);

			uvc->state = UVC_STATE_CONNECTED;
		}

		return 0;
	}

	if (interface != uvc->streaming_intf)
		return -EINVAL;

	/* TODO
	if (usb_endpoint_xfer_bulk(&uvc->desc.vs_ep))
		return alt ? -EINVAL : 0;
	*/

	switch (alt) {
	case 0:
		if (uvc->state != UVC_STATE_STREAMING)
			return 0;

		if (uvc->video.ep)
			usb_ep_disable(uvc->video.ep);

		memset(&v4l2_event, 0, sizeof(v4l2_event));
		v4l2_event.type = UVC_EVENT_STREAMOFF;
		v4l2_event_queue(&uvc->vdev, &v4l2_event);

		uvc->state = UVC_STATE_CONNECTED;
		return 0;

	case 1:
		if (uvc->state != UVC_STATE_CONNECTED)
			return 0;

		if (!uvc->video.ep)
			return -EINVAL;

		INFO(cdev, "reset UVC\n");
		usb_ep_disable(uvc->video.ep);

		ret = config_ep_by_speed(f->config->cdev->gadget,
				&(uvc->func), uvc->video.ep);
		if (ret)
			return ret;
		usb_ep_enable(uvc->video.ep);

		memset(&v4l2_event, 0, sizeof(v4l2_event));
		v4l2_event.type = UVC_EVENT_STREAMON;
		v4l2_event_queue(&uvc->vdev, &v4l2_event);
		return USB_GADGET_DELAYED_STATUS;

	default:
		return -EINVAL;
	}
}