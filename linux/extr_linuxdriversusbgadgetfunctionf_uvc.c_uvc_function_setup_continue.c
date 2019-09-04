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
struct TYPE_4__ {TYPE_1__* config; } ;
struct uvc_device {TYPE_2__ func; } ;
struct usb_composite_dev {int dummy; } ;
struct TYPE_3__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_composite_setup_continue (struct usb_composite_dev*) ; 

void uvc_function_setup_continue(struct uvc_device *uvc)
{
	struct usb_composite_dev *cdev = uvc->func.config->cdev;

	usb_composite_setup_continue(cdev);
}