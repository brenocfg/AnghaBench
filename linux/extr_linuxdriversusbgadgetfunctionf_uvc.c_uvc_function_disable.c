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
typedef  int /*<<< orphan*/  v4l2_event ;
struct v4l2_event {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  ep; } ;
struct uvc_device {int /*<<< orphan*/  control_ep; TYPE_1__ video; int /*<<< orphan*/  state; int /*<<< orphan*/  vdev; } ;
struct usb_function {TYPE_2__* config; } ;
struct TYPE_4__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UVC_EVENT_DISCONNECT ; 
 int /*<<< orphan*/  UVC_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  memset (struct v4l2_event*,int /*<<< orphan*/ ,int) ; 
 struct uvc_device* to_uvc (struct usb_function*) ; 
 int /*<<< orphan*/  usb_ep_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_event_queue (int /*<<< orphan*/ *,struct v4l2_event*) ; 

__attribute__((used)) static void
uvc_function_disable(struct usb_function *f)
{
	struct uvc_device *uvc = to_uvc(f);
	struct v4l2_event v4l2_event;

	INFO(f->config->cdev, "uvc_function_disable\n");

	memset(&v4l2_event, 0, sizeof(v4l2_event));
	v4l2_event.type = UVC_EVENT_DISCONNECT;
	v4l2_event_queue(&uvc->vdev, &v4l2_event);

	uvc->state = UVC_STATE_DISCONNECTED;

	usb_ep_disable(uvc->video.ep);
	usb_ep_disable(uvc->control_ep);
}