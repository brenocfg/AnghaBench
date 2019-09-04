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
struct usb_phy {int /*<<< orphan*/  chg_work; int /*<<< orphan*/  chg_state; int /*<<< orphan*/  chg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNKNOWN_TYPE ; 
 int /*<<< orphan*/  USB_CHARGER_DEFAULT ; 
 int /*<<< orphan*/  usb_phy_notify_charger_work ; 
 int /*<<< orphan*/  usb_phy_set_default_current (struct usb_phy*) ; 

__attribute__((used)) static void usb_charger_init(struct usb_phy *usb_phy)
{
	usb_phy->chg_type = UNKNOWN_TYPE;
	usb_phy->chg_state = USB_CHARGER_DEFAULT;
	usb_phy_set_default_current(usb_phy);
	INIT_WORK(&usb_phy->chg_work, usb_phy_notify_charger_work);
}