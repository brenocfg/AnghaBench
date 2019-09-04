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
struct isp1760_udc {int /*<<< orphan*/  irqname; int /*<<< orphan*/  irq; int /*<<< orphan*/  gadget; int /*<<< orphan*/  isp; } ;
struct isp1760_device {struct isp1760_udc udc; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct isp1760_udc*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

void isp1760_udc_unregister(struct isp1760_device *isp)
{
	struct isp1760_udc *udc = &isp->udc;

	if (!udc->isp)
		return;

	usb_del_gadget_udc(&udc->gadget);

	free_irq(udc->irq, udc);
	kfree(udc->irqname);
}