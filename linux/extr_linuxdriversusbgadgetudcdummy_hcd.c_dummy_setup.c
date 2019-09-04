#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* root_hub; int /*<<< orphan*/  sg_tablesize; int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_4__ self; int /*<<< orphan*/  speed; } ;
struct dummy {TYPE_2__* ss_hcd; TYPE_1__* hs_hcd; } ;
struct TYPE_7__ {int /*<<< orphan*/  speed; } ;
struct TYPE_6__ {struct dummy* dum; } ;
struct TYPE_5__ {struct dummy* dum; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_USB2 ; 
 int /*<<< orphan*/  HCD_USB3 ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 scalar_t__ dev_get_platdata (int /*<<< orphan*/ ) ; 
 void* hcd_to_dummy_hcd (struct usb_hcd*) ; 
 scalar_t__ usb_hcd_is_primary_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int dummy_setup(struct usb_hcd *hcd)
{
	struct dummy *dum;

	dum = *((void **)dev_get_platdata(hcd->self.controller));
	hcd->self.sg_tablesize = ~0;
	if (usb_hcd_is_primary_hcd(hcd)) {
		dum->hs_hcd = hcd_to_dummy_hcd(hcd);
		dum->hs_hcd->dum = dum;
		/*
		 * Mark the first roothub as being USB 2.0.
		 * The USB 3.0 roothub will be registered later by
		 * dummy_hcd_probe()
		 */
		hcd->speed = HCD_USB2;
		hcd->self.root_hub->speed = USB_SPEED_HIGH;
	} else {
		dum->ss_hcd = hcd_to_dummy_hcd(hcd);
		dum->ss_hcd->dum = dum;
		hcd->speed = HCD_USB3;
		hcd->self.root_hub->speed = USB_SPEED_SUPER;
	}
	return 0;
}