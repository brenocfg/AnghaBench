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
struct usb_phy {int chg_state; int /*<<< orphan*/  chg_work; int /*<<< orphan*/  chg_type; int /*<<< orphan*/  (* charger_detect ) (struct usb_phy*) ;} ;
typedef  enum usb_charger_state { ____Placeholder_usb_charger_state } usb_charger_state ;

/* Variables and functions */
 int /*<<< orphan*/  UNKNOWN_TYPE ; 
 scalar_t__ USB_CHARGER_PRESENT ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct usb_phy*) ; 

void usb_phy_set_charger_state(struct usb_phy *usb_phy,
			       enum usb_charger_state state)
{
	if (usb_phy->chg_state == state || !usb_phy->charger_detect)
		return;

	usb_phy->chg_state = state;
	if (usb_phy->chg_state == USB_CHARGER_PRESENT)
		usb_phy->chg_type = usb_phy->charger_detect(usb_phy);
	else
		usb_phy->chg_type = UNKNOWN_TYPE;

	schedule_work(&usb_phy->chg_work);
}