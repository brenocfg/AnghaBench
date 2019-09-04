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
struct usb_device {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_TIMEOUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USBDUX_CPU_CS ; 
 int /*<<< orphan*/  USBDUX_FIRMWARE_CMD ; 
 size_t USBDUX_FIRMWARE_MAX_LEN ; 
 int /*<<< orphan*/  VENDOR_DIR_OUT ; 
 struct usb_device* comedi_to_usb_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int* kmemdup (int const*,size_t,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbdux_firmware_upload(struct comedi_device *dev,
				  const u8 *data, size_t size,
				  unsigned long context)
{
	struct usb_device *usb = comedi_to_usb_dev(dev);
	u8 *buf;
	u8 *tmp;
	int ret;

	if (!data)
		return 0;

	if (size > USBDUX_FIRMWARE_MAX_LEN) {
		dev_err(dev->class_dev,
			"usbdux firmware binary it too large for FX2.\n");
		return -ENOMEM;
	}

	/* we generate a local buffer for the firmware */
	buf = kmemdup(data, size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	/* we need a malloc'ed buffer for usb_control_msg() */
	tmp = kmalloc(1, GFP_KERNEL);
	if (!tmp) {
		kfree(buf);
		return -ENOMEM;
	}

	/* stop the current firmware on the device */
	*tmp = 1;	/* 7f92 to one */
	ret = usb_control_msg(usb, usb_sndctrlpipe(usb, 0),
			      USBDUX_FIRMWARE_CMD,
			      VENDOR_DIR_OUT,
			      USBDUX_CPU_CS, 0x0000,
			      tmp, 1,
			      BULK_TIMEOUT);
	if (ret < 0) {
		dev_err(dev->class_dev, "can not stop firmware\n");
		goto done;
	}

	/* upload the new firmware to the device */
	ret = usb_control_msg(usb, usb_sndctrlpipe(usb, 0),
			      USBDUX_FIRMWARE_CMD,
			      VENDOR_DIR_OUT,
			      0, 0x0000,
			      buf, size,
			      BULK_TIMEOUT);
	if (ret < 0) {
		dev_err(dev->class_dev, "firmware upload failed\n");
		goto done;
	}

	/* start the new firmware on the device */
	*tmp = 0;	/* 7f92 to zero */
	ret = usb_control_msg(usb, usb_sndctrlpipe(usb, 0),
			      USBDUX_FIRMWARE_CMD,
			      VENDOR_DIR_OUT,
			      USBDUX_CPU_CS, 0x0000,
			      tmp, 1,
			      BULK_TIMEOUT);
	if (ret < 0)
		dev_err(dev->class_dev, "can not start firmware\n");

done:
	kfree(tmp);
	kfree(buf);
	return ret;
}