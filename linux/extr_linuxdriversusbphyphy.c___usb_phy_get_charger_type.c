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
struct usb_phy {int /*<<< orphan*/  chg_work; void* chg_state; int /*<<< orphan*/  chg_type; int /*<<< orphan*/  edev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACA_TYPE ; 
 int /*<<< orphan*/  CDP_TYPE ; 
 int /*<<< orphan*/  DCP_TYPE ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_ACA ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_CDP ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_DCP ; 
 int /*<<< orphan*/  EXTCON_CHG_USB_SDP ; 
 int /*<<< orphan*/  SDP_TYPE ; 
 int /*<<< orphan*/  UNKNOWN_TYPE ; 
 void* USB_CHARGER_ABSENT ; 
 void* USB_CHARGER_PRESENT ; 
 scalar_t__ extcon_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __usb_phy_get_charger_type(struct usb_phy *usb_phy)
{
	if (extcon_get_state(usb_phy->edev, EXTCON_CHG_USB_SDP) > 0) {
		usb_phy->chg_type = SDP_TYPE;
		usb_phy->chg_state = USB_CHARGER_PRESENT;
	} else if (extcon_get_state(usb_phy->edev, EXTCON_CHG_USB_CDP) > 0) {
		usb_phy->chg_type = CDP_TYPE;
		usb_phy->chg_state = USB_CHARGER_PRESENT;
	} else if (extcon_get_state(usb_phy->edev, EXTCON_CHG_USB_DCP) > 0) {
		usb_phy->chg_type = DCP_TYPE;
		usb_phy->chg_state = USB_CHARGER_PRESENT;
	} else if (extcon_get_state(usb_phy->edev, EXTCON_CHG_USB_ACA) > 0) {
		usb_phy->chg_type = ACA_TYPE;
		usb_phy->chg_state = USB_CHARGER_PRESENT;
	} else {
		usb_phy->chg_type = UNKNOWN_TYPE;
		usb_phy->chg_state = USB_CHARGER_ABSENT;
	}

	schedule_work(&usb_phy->chg_work);
}