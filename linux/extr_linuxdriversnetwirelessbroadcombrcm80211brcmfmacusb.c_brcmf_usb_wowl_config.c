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
struct brcmf_usbdev_info {int wowl_enabled; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct brcmf_usbdev_info* brcmf_usb_get_businfo (struct device*) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void brcmf_usb_wowl_config(struct device *dev, bool enabled)
{
	struct brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(dev);

	brcmf_dbg(USB, "Configuring WOWL, enabled=%d\n", enabled);
	devinfo->wowl_enabled = enabled;
	if (enabled)
		device_set_wakeup_enable(devinfo->dev, true);
	else
		device_set_wakeup_enable(devinfo->dev, false);
}