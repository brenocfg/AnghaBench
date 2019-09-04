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
struct usb_phy {int dummy; } ;
struct phy_companion {int dummy; } ;
struct omap_usb {struct phy_companion* comparator; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct usb_phy*) ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 struct omap_usb* phy_to_omapusb (struct usb_phy*) ; 
 struct usb_phy* usb_get_phy (int /*<<< orphan*/ ) ; 

int omap_usb2_set_comparator(struct phy_companion *comparator)
{
	struct omap_usb	*phy;
	struct usb_phy	*x = usb_get_phy(USB_PHY_TYPE_USB2);

	if (IS_ERR(x))
		return -ENODEV;

	phy = phy_to_omapusb(x);
	phy->comparator = comparator;
	return 0;
}