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
struct usb_composite_driver {int /*<<< orphan*/  gadget_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_gadget_unregister_driver (int /*<<< orphan*/ *) ; 

void usb_composite_unregister(struct usb_composite_driver *driver)
{
	usb_gadget_unregister_driver(&driver->gadget_driver);
}