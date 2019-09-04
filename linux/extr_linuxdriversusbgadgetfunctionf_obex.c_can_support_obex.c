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
struct usb_configuration {TYPE_1__* cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  gadget_is_altset_supported (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool can_support_obex(struct usb_configuration *c)
{
	/* Since the first interface is a NOP, we can ignore the
	 * issue of multi-interface support on most controllers.
	 *
	 * Altsettings are mandatory, however...
	 */
	if (!gadget_is_altset_supported(c->cdev->gadget))
		return false;

	/* everything else is *probably* fine ... */
	return true;
}