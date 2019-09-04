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
struct TYPE_6__ {TYPE_2__* ep; } ;
struct uvc_device {unsigned int control_intf; unsigned int streaming_intf; TYPE_3__ video; } ;
struct usb_function {TYPE_1__* config; } ;
struct TYPE_5__ {scalar_t__ enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INFO (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct uvc_device* to_uvc (struct usb_function*) ; 

__attribute__((used)) static int
uvc_function_get_alt(struct usb_function *f, unsigned interface)
{
	struct uvc_device *uvc = to_uvc(f);

	INFO(f->config->cdev, "uvc_function_get_alt(%u)\n", interface);

	if (interface == uvc->control_intf)
		return 0;
	else if (interface != uvc->streaming_intf)
		return -EINVAL;
	else
		return uvc->video.ep->enabled ? 1 : 0;
}