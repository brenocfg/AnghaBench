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
typedef  int /*<<< orphan*/  u32 ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct snd_usb_audio {struct usb_device* dev; } ;

/* Variables and functions */
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 int snd_usb_ctl_msg (struct usb_device*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_rme_read_value(struct snd_usb_audio *chip,
			      unsigned int item,
			      u32 *value)
{
	struct usb_device *dev = chip->dev;
	int err;

	err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0),
			      item,
			      USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0, 0,
			      value, sizeof(*value));
	if (err < 0)
		dev_err(&dev->dev,
			"unable to issue vendor read request %d (ret = %d)",
			item, err);
	return err;
}