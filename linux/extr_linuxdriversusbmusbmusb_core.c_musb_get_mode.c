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
struct device {int dummy; } ;
typedef  enum usb_dr_mode { ____Placeholder_usb_dr_mode } usb_dr_mode ;
typedef  enum musb_mode { ____Placeholder_musb_mode } musb_mode ;

/* Variables and functions */
 int MUSB_HOST ; 
 int MUSB_OTG ; 
 int MUSB_PERIPHERAL ; 
#define  USB_DR_MODE_HOST 131 
#define  USB_DR_MODE_OTG 130 
#define  USB_DR_MODE_PERIPHERAL 129 
#define  USB_DR_MODE_UNKNOWN 128 
 int usb_get_dr_mode (struct device*) ; 

enum musb_mode musb_get_mode(struct device *dev)
{
	enum usb_dr_mode mode;

	mode = usb_get_dr_mode(dev);
	switch (mode) {
	case USB_DR_MODE_HOST:
		return MUSB_HOST;
	case USB_DR_MODE_PERIPHERAL:
		return MUSB_PERIPHERAL;
	case USB_DR_MODE_OTG:
	case USB_DR_MODE_UNKNOWN:
	default:
		return MUSB_OTG;
	}
}