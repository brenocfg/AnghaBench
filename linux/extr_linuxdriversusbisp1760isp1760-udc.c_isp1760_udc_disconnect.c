#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ state; int /*<<< orphan*/  speed; } ;
struct isp1760_udc {int /*<<< orphan*/  vbus_timer; TYPE_3__ gadget; TYPE_1__* driver; TYPE_2__* isp; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* disconnect ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  USB_STATE_ATTACHED ; 
 scalar_t__ USB_STATE_POWERED ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_gadget_set_state (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isp1760_udc_disconnect(struct isp1760_udc *udc)
{
	if (udc->gadget.state < USB_STATE_POWERED)
		return;

	dev_dbg(udc->isp->dev, "Device disconnected in state %u\n",
		 udc->gadget.state);

	udc->gadget.speed = USB_SPEED_UNKNOWN;
	usb_gadget_set_state(&udc->gadget, USB_STATE_ATTACHED);

	if (udc->driver->disconnect)
		udc->driver->disconnect(&udc->gadget);

	del_timer(&udc->vbus_timer);

	/* TODO Reset all endpoints ? */
}