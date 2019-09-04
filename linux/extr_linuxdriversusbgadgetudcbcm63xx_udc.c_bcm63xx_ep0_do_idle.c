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
struct TYPE_2__ {int /*<<< orphan*/  req; } ;
struct bcm63xx_udc {scalar_t__ ep0state; int /*<<< orphan*/  dev; scalar_t__ ep0_reply; TYPE_1__ ep0_ctrl_req; int /*<<< orphan*/  gadget; int /*<<< orphan*/ * iudma; int /*<<< orphan*/ * ep0_request; scalar_t__ ep0_req_completed; scalar_t__ ep0_req_shutdown; scalar_t__ ep0_req_set_iface; scalar_t__ ep0_req_set_cfg; scalar_t__ ep0_req_reset; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ EP0_IDLE ; 
 void* EP0_IN_FAKE_STATUS_PHASE ; 
 scalar_t__ EP0_SHUTDOWN ; 
 size_t IUDMA_EP0_RXCHAN ; 
 scalar_t__ bcm63xx_ep0_do_setup (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  bcm63xx_ep0_nuke_reply (struct bcm63xx_udc*,int /*<<< orphan*/ ) ; 
 scalar_t__ bcm63xx_ep0_spoof_set_cfg (struct bcm63xx_udc*) ; 
 scalar_t__ bcm63xx_ep0_spoof_set_iface (struct bcm63xx_udc*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iudma_reset_channel (struct bcm63xx_udc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  usb_gadget_unmap_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm63xx_ep0_do_idle(struct bcm63xx_udc *udc)
{
	if (udc->ep0_req_reset) {
		udc->ep0_req_reset = 0;
	} else if (udc->ep0_req_set_cfg) {
		udc->ep0_req_set_cfg = 0;
		if (bcm63xx_ep0_spoof_set_cfg(udc) >= 0)
			udc->ep0state = EP0_IN_FAKE_STATUS_PHASE;
	} else if (udc->ep0_req_set_iface) {
		udc->ep0_req_set_iface = 0;
		if (bcm63xx_ep0_spoof_set_iface(udc) >= 0)
			udc->ep0state = EP0_IN_FAKE_STATUS_PHASE;
	} else if (udc->ep0_req_completed) {
		udc->ep0state = bcm63xx_ep0_do_setup(udc);
		return udc->ep0state == EP0_IDLE ? -EAGAIN : 0;
	} else if (udc->ep0_req_shutdown) {
		udc->ep0_req_shutdown = 0;
		udc->ep0_req_completed = 0;
		udc->ep0_request = NULL;
		iudma_reset_channel(udc, &udc->iudma[IUDMA_EP0_RXCHAN]);
		usb_gadget_unmap_request(&udc->gadget,
			&udc->ep0_ctrl_req.req, 0);

		/* bcm63xx_udc_pullup() is waiting for this */
		mb();
		udc->ep0state = EP0_SHUTDOWN;
	} else if (udc->ep0_reply) {
		/*
		 * This could happen if a USB RESET shows up during an ep0
		 * transaction (especially if a laggy driver like gadgetfs
		 * is in use).
		 */
		dev_warn(udc->dev, "nuking unexpected reply\n");
		bcm63xx_ep0_nuke_reply(udc, 0);
	} else {
		return -EAGAIN;
	}

	return 0;
}