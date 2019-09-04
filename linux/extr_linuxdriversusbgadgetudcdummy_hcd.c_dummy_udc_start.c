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
struct usb_gadget_driver {scalar_t__ max_speed; } ;
struct usb_gadget {int dummy; } ;
struct dummy_hcd {struct dummy* dum; } ;
struct dummy {int ints_enabled; int /*<<< orphan*/  lock; struct usb_gadget_driver* driver; scalar_t__ devstatus; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 struct dummy_hcd* gadget_to_dummy_hcd (struct usb_gadget*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dummy_udc_start(struct usb_gadget *g,
		struct usb_gadget_driver *driver)
{
	struct dummy_hcd	*dum_hcd = gadget_to_dummy_hcd(g);
	struct dummy		*dum = dum_hcd->dum;

	if (driver->max_speed == USB_SPEED_UNKNOWN)
		return -EINVAL;

	/*
	 * SLAVE side init ... the layer above hardware, which
	 * can't enumerate without help from the driver we're binding.
	 */

	spin_lock_irq(&dum->lock);
	dum->devstatus = 0;
	dum->driver = driver;
	dum->ints_enabled = 1;
	spin_unlock_irq(&dum->lock);

	return 0;
}