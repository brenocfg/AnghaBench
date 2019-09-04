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
struct TYPE_2__ {int /*<<< orphan*/ * bus; } ;
struct usb_gadget_driver {TYPE_1__ driver; } ;
struct usb_gadget {int dummy; } ;
struct goku_udc {struct usb_gadget_driver* driver; } ;

/* Variables and functions */
 struct goku_udc* to_goku_udc (struct usb_gadget*) ; 
 int /*<<< orphan*/  udc_enable (struct goku_udc*) ; 

__attribute__((used)) static int goku_udc_start(struct usb_gadget *g,
		struct usb_gadget_driver *driver)
{
	struct goku_udc	*dev = to_goku_udc(g);

	/* hook up the driver */
	driver->driver.bus = NULL;
	dev->driver = driver;

	/*
	 * then enable host detection and ep0; and we're ready
	 * for set_configuration as well as eventual disconnect.
	 */
	udc_enable(dev);

	return 0;
}