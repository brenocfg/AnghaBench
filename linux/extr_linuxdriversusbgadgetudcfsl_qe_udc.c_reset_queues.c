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
typedef  scalar_t__ u8 ;
struct qe_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/  driver; int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 scalar_t__ USB_MAX_ENDPOINTS ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_reset_ep_queue (struct qe_udc*,scalar_t__) ; 
 int /*<<< orphan*/  usb_gadget_udc_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reset_queues(struct qe_udc *udc)
{
	u8 pipe;

	for (pipe = 0; pipe < USB_MAX_ENDPOINTS; pipe++)
		udc_reset_ep_queue(udc, pipe);

	/* report disconnect; the driver is already quiesced */
	spin_unlock(&udc->lock);
	usb_gadget_udc_reset(&udc->gadget, udc->driver);
	spin_lock(&udc->lock);

	return 0;
}