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
struct usbduxsigma_private {int* dux_commands; } ;
struct usb_device {int dummy; } ;
struct comedi_device {struct usbduxsigma_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_TIMEOUT ; 
 int /*<<< orphan*/  SIZEOFDUXBUFFER ; 
 struct usb_device* comedi_to_usb_dev (struct comedi_device*) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static int usbbuxsigma_send_cmd(struct comedi_device *dev, int cmd_type)
{
	struct usb_device *usb = comedi_to_usb_dev(dev);
	struct usbduxsigma_private *devpriv = dev->private;
	int nsent;

	devpriv->dux_commands[0] = cmd_type;

	return usb_bulk_msg(usb, usb_sndbulkpipe(usb, 1),
			    devpriv->dux_commands, SIZEOFDUXBUFFER,
			    &nsent, BULK_TIMEOUT);
}