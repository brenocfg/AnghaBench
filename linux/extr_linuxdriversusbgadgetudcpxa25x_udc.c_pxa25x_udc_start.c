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
struct usb_gadget_driver {int dummy; } ;
struct usb_gadget {int dummy; } ;
struct pxa25x_udc {int pullup; int /*<<< orphan*/  gadget; TYPE_1__* transceiver; struct usb_gadget_driver* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_state (struct pxa25x_udc*) ; 
 int otg_set_peripheral (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pxa25x_udc* to_pxa25x (struct usb_gadget*) ; 

__attribute__((used)) static int pxa25x_udc_start(struct usb_gadget *g,
		struct usb_gadget_driver *driver)
{
	struct pxa25x_udc	*dev = to_pxa25x(g);
	int			retval;

	/* first hook up the driver ... */
	dev->driver = driver;
	dev->pullup = 1;

	/* ... then enable host detection and ep0; and we're ready
	 * for set_configuration as well as eventual disconnect.
	 */
	/* connect to bus through transceiver */
	if (!IS_ERR_OR_NULL(dev->transceiver)) {
		retval = otg_set_peripheral(dev->transceiver->otg,
						&dev->gadget);
		if (retval)
			goto bind_fail;
	}

	dump_state(dev);
	return 0;
bind_fail:
	return retval;
}