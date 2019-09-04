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
struct usb_request {int status; int /*<<< orphan*/  (* complete ) (int /*<<< orphan*/ *,struct usb_request*) ;scalar_t__ actual; } ;
struct bcm63xx_udc {int /*<<< orphan*/  lock; TYPE_1__* bep; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct usb_request*) ; 

__attribute__((used)) static void bcm63xx_ep0_complete(struct bcm63xx_udc *udc,
	struct usb_request *req, int status)
{
	req->status = status;
	if (status)
		req->actual = 0;
	if (req->complete) {
		spin_unlock_irq(&udc->lock);
		req->complete(&udc->bep[0].ep, req);
		spin_lock_irq(&udc->lock);
	}
}