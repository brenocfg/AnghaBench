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
struct omap_control_phy {scalar_t__ type; } ;
struct device {int dummy; } ;
typedef  enum omap_control_usb_mode { ____Placeholder_omap_control_usb_mode } omap_control_usb_mode ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 scalar_t__ OMAP_CTRL_TYPE_OTGHS ; 
#define  USB_MODE_DEVICE 130 
#define  USB_MODE_DISCONNECT 129 
#define  USB_MODE_HOST 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct omap_control_phy* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*) ; 
 int /*<<< orphan*/  omap_control_usb_device_mode (struct omap_control_phy*) ; 
 int /*<<< orphan*/  omap_control_usb_host_mode (struct omap_control_phy*) ; 
 int /*<<< orphan*/  omap_control_usb_set_sessionend (struct omap_control_phy*) ; 

void omap_control_usb_set_mode(struct device *dev,
	enum omap_control_usb_mode mode)
{
	struct omap_control_phy	*ctrl_phy;

	if (IS_ERR(dev) || !dev)
		return;

	ctrl_phy = dev_get_drvdata(dev);
	if (!ctrl_phy) {
		dev_err(dev, "Invalid control phy device\n");
		return;
	}

	if (ctrl_phy->type != OMAP_CTRL_TYPE_OTGHS)
		return;

	switch (mode) {
	case USB_MODE_HOST:
		omap_control_usb_host_mode(ctrl_phy);
		break;
	case USB_MODE_DEVICE:
		omap_control_usb_device_mode(ctrl_phy);
		break;
	case USB_MODE_DISCONNECT:
		omap_control_usb_set_sessionend(ctrl_phy);
		break;
	default:
		dev_vdbg(dev, "invalid omap control usb mode\n");
	}
}