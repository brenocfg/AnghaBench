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
struct usb_gadget {int dummy; } ;
struct pxa_udc {TYPE_1__* transceiver; int /*<<< orphan*/ * driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_1__*) ; 
 int otg_set_peripheral (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_activity (struct pxa_udc*) ; 
 struct pxa_udc* to_pxa (struct usb_gadget*) ; 
 int /*<<< orphan*/  udc_disable (struct pxa_udc*) ; 

__attribute__((used)) static int pxa27x_udc_stop(struct usb_gadget *g)
{
	struct pxa_udc *udc = to_pxa(g);

	stop_activity(udc);
	udc_disable(udc);

	udc->driver = NULL;

	if (!IS_ERR_OR_NULL(udc->transceiver))
		return otg_set_peripheral(udc->transceiver->otg, NULL);
	return 0;
}