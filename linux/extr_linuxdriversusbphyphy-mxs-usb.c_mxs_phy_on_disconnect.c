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
struct usb_phy {scalar_t__ io_priv; int /*<<< orphan*/  dev; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;

/* Variables and functions */
 int BM_USBPHY_CTRL_ENHOSTDISCONDETECT ; 
 scalar_t__ HW_USBPHY_CTRL ; 
 scalar_t__ HW_USBPHY_CTRL_CLR ; 
 int USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxs_phy_on_disconnect(struct usb_phy *phy,
		enum usb_device_speed speed)
{
	dev_dbg(phy->dev, "%s device has disconnected\n",
		(speed == USB_SPEED_HIGH) ? "HS" : "FS/LS");

	/* Sometimes, the speed is not high speed when the error occurs */
	if (readl(phy->io_priv + HW_USBPHY_CTRL) &
			BM_USBPHY_CTRL_ENHOSTDISCONDETECT)
		writel(BM_USBPHY_CTRL_ENHOSTDISCONDETECT,
		       phy->io_priv + HW_USBPHY_CTRL_CLR);

	return 0;
}