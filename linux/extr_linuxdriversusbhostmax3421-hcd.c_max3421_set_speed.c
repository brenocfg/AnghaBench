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
typedef  int u8 ;
struct usb_hcd {int dummy; } ;
struct usb_device {scalar_t__ speed; } ;
struct max3421_hcd {int mode; int port_status; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX3421_MODE_HUBPRE_BIT ; 
 int /*<<< orphan*/  MAX3421_MODE_LOWSPEED_BIT ; 
 int /*<<< orphan*/  MAX3421_REG_MODE ; 
 int USB_PORT_STAT_LOW_SPEED ; 
 scalar_t__ USB_SPEED_LOW ; 
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 
 int /*<<< orphan*/  spi_wr8 (struct usb_hcd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
max3421_set_speed(struct usb_hcd *hcd, struct usb_device *dev)
{
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u8 mode_lowspeed, mode_hubpre, mode = max3421_hcd->mode;

	mode_lowspeed = BIT(MAX3421_MODE_LOWSPEED_BIT);
	mode_hubpre   = BIT(MAX3421_MODE_HUBPRE_BIT);
	if (max3421_hcd->port_status & USB_PORT_STAT_LOW_SPEED) {
		mode |=  mode_lowspeed;
		mode &= ~mode_hubpre;
	} else if (dev->speed == USB_SPEED_LOW) {
		mode |= mode_lowspeed | mode_hubpre;
	} else {
		mode &= ~(mode_lowspeed | mode_hubpre);
	}
	if (mode != max3421_hcd->mode) {
		max3421_hcd->mode = mode;
		spi_wr8(hcd, MAX3421_REG_MODE, max3421_hcd->mode);
	}

}