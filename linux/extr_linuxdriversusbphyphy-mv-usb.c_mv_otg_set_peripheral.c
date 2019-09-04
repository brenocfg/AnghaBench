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
struct usb_otg {struct usb_gadget* gadget; } ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int mv_otg_set_peripheral(struct usb_otg *otg,
				 struct usb_gadget *gadget)
{
	otg->gadget = gadget;

	return 0;
}