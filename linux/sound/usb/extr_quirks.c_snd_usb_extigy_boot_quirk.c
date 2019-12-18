#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct usb_host_config {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; struct usb_host_config* actconfig; int /*<<< orphan*/  descriptor; } ;
struct TYPE_2__ {int /*<<< orphan*/  wTotalLength; } ;

/* Variables and functions */
 int ENODEV ; 
 int EXTIGY_FIRMWARE_SIZE_NEW ; 
 int EXTIGY_FIRMWARE_SIZE_OLD ; 
 int /*<<< orphan*/  USB_DT_DEVICE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__* get_cfg_desc (struct usb_host_config*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int snd_usb_ctl_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int usb_get_descriptor (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int usb_reset_configuration (struct usb_device*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_usb_extigy_boot_quirk(struct usb_device *dev, struct usb_interface *intf)
{
	struct usb_host_config *config = dev->actconfig;
	int err;

	if (le16_to_cpu(get_cfg_desc(config)->wTotalLength) == EXTIGY_FIRMWARE_SIZE_OLD ||
	    le16_to_cpu(get_cfg_desc(config)->wTotalLength) == EXTIGY_FIRMWARE_SIZE_NEW) {
		dev_dbg(&dev->dev, "sending Extigy boot sequence...\n");
		/* Send message to force it to reconnect with full interface. */
		err = snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev,0),
				      0x10, 0x43, 0x0001, 0x000a, NULL, 0);
		if (err < 0)
			dev_dbg(&dev->dev, "error sending boot message: %d\n", err);
		err = usb_get_descriptor(dev, USB_DT_DEVICE, 0,
				&dev->descriptor, sizeof(dev->descriptor));
		config = dev->actconfig;
		if (err < 0)
			dev_dbg(&dev->dev, "error usb_get_descriptor: %d\n", err);
		err = usb_reset_configuration(dev);
		if (err < 0)
			dev_dbg(&dev->dev, "error usb_reset_configuration: %d\n", err);
		dev_dbg(&dev->dev, "extigy_boot: new boot length = %d\n",
			    le16_to_cpu(get_cfg_desc(config)->wTotalLength));
		return -ENODEV; /* quit this anyway */
	}
	return 0;
}