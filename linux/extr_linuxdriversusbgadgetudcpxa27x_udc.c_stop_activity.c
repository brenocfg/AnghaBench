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
struct TYPE_3__ {int /*<<< orphan*/  speed; } ;
struct pxa_udc {TYPE_2__* udc_usb_ep; TYPE_1__ gadget; } ;
struct TYPE_4__ {int /*<<< orphan*/  usb_ep; } ;

/* Variables and functions */
 int NR_USB_ENDPOINTS ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  pxa_ep_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_activity(struct pxa_udc *udc)
{
	int i;

	udc->gadget.speed = USB_SPEED_UNKNOWN;

	for (i = 0; i < NR_USB_ENDPOINTS; i++)
		pxa_ep_disable(&udc->udc_usb_ep[i].usb_ep);
}