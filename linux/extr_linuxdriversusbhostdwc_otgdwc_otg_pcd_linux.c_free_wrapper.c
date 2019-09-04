#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct gadget_wrapper {TYPE_3__ gadget; TYPE_2__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_FREE (struct gadget_wrapper*) ; 
 int /*<<< orphan*/  DWC_WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_wrapper(struct gadget_wrapper *d)
{
	if (d->driver) {
		/* should have been done already by driver model core */
		DWC_WARN("driver '%s' is still registered\n",
			 d->driver->driver.name);
#ifdef CONFIG_USB_GADGET
		usb_gadget_unregister_driver(d->driver);
#endif
	}

	device_unregister(&d->gadget.dev);
	DWC_FREE(d);
}