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
struct usb_otg {int /*<<< orphan*/  usb_phy; } ;
struct usb_gadget {int dummy; } ;
struct TYPE_4__ {TYPE_1__* otg; } ;
struct ab8500_usb {scalar_t__ mode; int /*<<< orphan*/  phy_dis_work; TYPE_2__ phy; } ;
struct TYPE_3__ {struct usb_gadget* gadget; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ USB_IDLE ; 
 struct ab8500_usb* phy_to_ab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ab8500_usb_set_peripheral(struct usb_otg *otg,
					struct usb_gadget *gadget)
{
	struct ab8500_usb *ab;

	if (!otg)
		return -ENODEV;

	ab = phy_to_ab(otg->usb_phy);

	ab->phy.otg->gadget = gadget;

	/* Some drivers call this function in atomic context.
	 * Do not update ab8500 registers directly till this
	 * is fixed.
	 */

	if ((ab->mode != USB_IDLE) && !gadget) {
		ab->mode = USB_IDLE;
		schedule_work(&ab->phy_dis_work);
	}

	return 0;
}