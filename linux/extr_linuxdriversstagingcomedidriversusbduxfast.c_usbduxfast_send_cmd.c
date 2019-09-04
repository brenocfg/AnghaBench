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
struct usbduxfast_private {int* duxbuf; } ;
struct usb_device {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct usbduxfast_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNELLISTEP ; 
 int /*<<< orphan*/  SIZEOFDUXBUF ; 
 struct usb_device* comedi_to_usb_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbduxfast_send_cmd(struct comedi_device *dev, int cmd_type)
{
	struct usb_device *usb = comedi_to_usb_dev(dev);
	struct usbduxfast_private *devpriv = dev->private;
	int nsent;
	int ret;

	devpriv->duxbuf[0] = cmd_type;

	ret = usb_bulk_msg(usb, usb_sndbulkpipe(usb, CHANNELLISTEP),
			   devpriv->duxbuf, SIZEOFDUXBUF,
			   &nsent, 10000);
	if (ret < 0)
		dev_err(dev->class_dev,
			"could not transmit command to the usb-device, err=%d\n",
			ret);
	return ret;
}