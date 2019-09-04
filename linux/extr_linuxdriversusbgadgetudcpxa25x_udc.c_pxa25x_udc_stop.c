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
struct pxa25x_udc {int /*<<< orphan*/ * driver; TYPE_1__* transceiver; scalar_t__ pullup; } ;
struct TYPE_2__ {int /*<<< orphan*/  otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_state (struct pxa25x_udc*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  otg_set_peripheral (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_activity (struct pxa25x_udc*,int /*<<< orphan*/ *) ; 
 struct pxa25x_udc* to_pxa25x (struct usb_gadget*) ; 

__attribute__((used)) static int pxa25x_udc_stop(struct usb_gadget*g)
{
	struct pxa25x_udc	*dev = to_pxa25x(g);

	local_irq_disable();
	dev->pullup = 0;
	stop_activity(dev, NULL);
	local_irq_enable();

	if (!IS_ERR_OR_NULL(dev->transceiver))
		(void) otg_set_peripheral(dev->transceiver->otg, NULL);

	dev->driver = NULL;

	dump_state(dev);

	return 0;
}