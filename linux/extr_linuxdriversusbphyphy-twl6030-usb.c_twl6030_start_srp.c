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
struct twl6030_usb {int dummy; } ;
struct phy_companion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL_MODULE_USB ; 
 int /*<<< orphan*/  USB_VBUS_CTRL_CLR ; 
 int /*<<< orphan*/  USB_VBUS_CTRL_SET ; 
 struct twl6030_usb* comparator_to_twl (struct phy_companion*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  twl6030_writeb (struct twl6030_usb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030_start_srp(struct phy_companion *comparator)
{
	struct twl6030_usb *twl = comparator_to_twl(comparator);

	twl6030_writeb(twl, TWL_MODULE_USB, 0x24, USB_VBUS_CTRL_SET);
	twl6030_writeb(twl, TWL_MODULE_USB, 0x84, USB_VBUS_CTRL_SET);

	mdelay(100);
	twl6030_writeb(twl, TWL_MODULE_USB, 0xa0, USB_VBUS_CTRL_CLR);

	return 0;
}