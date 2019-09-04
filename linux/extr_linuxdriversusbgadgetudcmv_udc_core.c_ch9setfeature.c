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
typedef  int u8 ;
struct usb_ctrlrequest {int bRequestType; int wValue; int wIndex; int /*<<< orphan*/  wLength; } ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct mv_udc {int remote_wakeup; int max_eps; int /*<<< orphan*/  lock; int /*<<< orphan*/  usb_state; TYPE_1__ gadget; } ;

/* Variables and functions */
 int EP_DIR_IN ; 
 int EP_DIR_OUT ; 
#define  USB_DEVICE_REMOTE_WAKEUP 130 
#define  USB_DEVICE_TEST_MODE 129 
 int USB_ENDPOINT_DIR_MASK ; 
#define  USB_ENDPOINT_HALT 128 
 int USB_ENDPOINT_NUMBER_MASK ; 
 int USB_RECIP_DEVICE ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_RECIP_MASK ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_STATE_ADDRESS ; 
 int /*<<< orphan*/  USB_STATE_CONFIGURED ; 
 int /*<<< orphan*/  USB_STATE_DEFAULT ; 
 int USB_TYPE_MASK ; 
 int USB_TYPE_STANDARD ; 
 int /*<<< orphan*/  ep0_stall (struct mv_udc*) ; 
 int /*<<< orphan*/  ep_set_stall (struct mv_udc*,int,int,int) ; 
 int /*<<< orphan*/  mv_udc_testmode (struct mv_udc*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ udc_prime_status (struct mv_udc*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ch9setfeature(struct mv_udc *udc, struct usb_ctrlrequest *setup)
{
	u8 ep_num;
	u8 direction;

	if ((setup->bRequestType & (USB_TYPE_MASK | USB_RECIP_MASK))
		== ((USB_TYPE_STANDARD | USB_RECIP_DEVICE))) {
		switch (setup->wValue) {
		case USB_DEVICE_REMOTE_WAKEUP:
			udc->remote_wakeup = 1;
			break;
		case USB_DEVICE_TEST_MODE:
			if (setup->wIndex & 0xFF
				||  udc->gadget.speed != USB_SPEED_HIGH)
				ep0_stall(udc);

			if (udc->usb_state != USB_STATE_CONFIGURED
				&& udc->usb_state != USB_STATE_ADDRESS
				&& udc->usb_state != USB_STATE_DEFAULT)
				ep0_stall(udc);

			mv_udc_testmode(udc, (setup->wIndex >> 8));
			goto out;
		default:
			goto out;
		}
	} else if ((setup->bRequestType & (USB_TYPE_MASK | USB_RECIP_MASK))
		== ((USB_TYPE_STANDARD | USB_RECIP_ENDPOINT))) {
		switch (setup->wValue) {
		case USB_ENDPOINT_HALT:
			ep_num = setup->wIndex & USB_ENDPOINT_NUMBER_MASK;
			direction = (setup->wIndex & USB_ENDPOINT_DIR_MASK)
				? EP_DIR_IN : EP_DIR_OUT;
			if (setup->wValue != 0 || setup->wLength != 0
				|| ep_num > udc->max_eps)
				goto out;
			spin_unlock(&udc->lock);
			ep_set_stall(udc, ep_num, direction, 1);
			spin_lock(&udc->lock);
			break;
		default:
			goto out;
		}
	} else
		goto out;

	if (udc_prime_status(udc, EP_DIR_IN, 0, true))
		ep0_stall(udc);
out:
	return;
}