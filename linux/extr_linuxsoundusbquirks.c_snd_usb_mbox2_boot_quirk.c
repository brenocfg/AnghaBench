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
typedef  int u8 ;
struct usb_host_config {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; struct usb_host_config* actconfig; int /*<<< orphan*/  descriptor; } ;
struct TYPE_2__ {int /*<<< orphan*/  wTotalLength; } ;

/* Variables and functions */
 int ENODEV ; 
 int MBOX2_BOOT_LOADING ; 
 int MBOX2_BOOT_READY ; 
 int MBOX2_FIRMWARE_SIZE ; 
 int /*<<< orphan*/  USB_DT_DEVICE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* get_cfg_desc (struct usb_host_config*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox2_setup_48_24_magic (struct usb_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_usb_ctl_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int,int**,int) ; 
 int usb_get_descriptor (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_reset_configuration (struct usb_device*) ; 

__attribute__((used)) static int snd_usb_mbox2_boot_quirk(struct usb_device *dev)
{
	struct usb_host_config *config = dev->actconfig;
	int err;
	u8 bootresponse[0x12];
	int fwsize;
	int count;

	fwsize = le16_to_cpu(get_cfg_desc(config)->wTotalLength);

	if (fwsize != MBOX2_FIRMWARE_SIZE) {
		dev_err(&dev->dev, "Invalid firmware size=%d.\n", fwsize);
		return -ENODEV;
	}

	dev_dbg(&dev->dev, "Sending Digidesign Mbox 2 boot sequence...\n");

	count = 0;
	bootresponse[0] = MBOX2_BOOT_LOADING;
	while ((bootresponse[0] == MBOX2_BOOT_LOADING) && (count < 10)) {
		msleep(500); /* 0.5 second delay */
		snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0),
			/* Control magic - load onboard firmware */
			0x85, 0xc0, 0x0001, 0x0000, &bootresponse, 0x0012);
		if (bootresponse[0] == MBOX2_BOOT_READY)
			break;
		dev_dbg(&dev->dev, "device not ready, resending boot sequence...\n");
		count++;
	}

	if (bootresponse[0] != MBOX2_BOOT_READY) {
		dev_err(&dev->dev, "Unknown bootresponse=%d, or timed out, ignoring device.\n", bootresponse[0]);
		return -ENODEV;
	}

	dev_dbg(&dev->dev, "device initialised!\n");

	err = usb_get_descriptor(dev, USB_DT_DEVICE, 0,
		&dev->descriptor, sizeof(dev->descriptor));
	config = dev->actconfig;
	if (err < 0)
		dev_dbg(&dev->dev, "error usb_get_descriptor: %d\n", err);

	err = usb_reset_configuration(dev);
	if (err < 0)
		dev_dbg(&dev->dev, "error usb_reset_configuration: %d\n", err);
	dev_dbg(&dev->dev, "mbox2_boot: new boot length = %d\n",
		le16_to_cpu(get_cfg_desc(config)->wTotalLength));

	mbox2_setup_48_24_magic(dev);

	dev_info(&dev->dev, "Digidesign Mbox 2: 24bit 48kHz");

	return 0; /* Successful boot */
}