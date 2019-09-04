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
struct qe_udc {scalar_t__ usb_state; int /*<<< orphan*/  ep0_dir; int /*<<< orphan*/  ep0_state; TYPE_1__* eps; TYPE_2__* usb_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  usb_usadr; } ;
struct TYPE_3__ {scalar_t__ init; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DIR_OUT ; 
 unsigned char USB_MAX_ENDPOINTS ; 
 scalar_t__ USB_STATE_DEFAULT ; 
 int /*<<< orphan*/  WAIT_FOR_SETUP ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_ep_reset (struct qe_udc*,unsigned char) ; 
 int /*<<< orphan*/  qe_usb_disable (struct qe_udc*) ; 
 int /*<<< orphan*/  qe_usb_enable (struct qe_udc*) ; 
 int /*<<< orphan*/  reset_queues (struct qe_udc*) ; 

__attribute__((used)) static int reset_irq(struct qe_udc *udc)
{
	unsigned char i;

	if (udc->usb_state == USB_STATE_DEFAULT)
		return 0;

	qe_usb_disable(udc);
	out_8(&udc->usb_regs->usb_usadr, 0);

	for (i = 0; i < USB_MAX_ENDPOINTS; i++) {
		if (udc->eps[i].init)
			qe_ep_reset(udc, i);
	}

	reset_queues(udc);
	udc->usb_state = USB_STATE_DEFAULT;
	udc->ep0_state = WAIT_FOR_SETUP;
	udc->ep0_dir = USB_DIR_OUT;
	qe_usb_enable(udc);
	return 0;
}