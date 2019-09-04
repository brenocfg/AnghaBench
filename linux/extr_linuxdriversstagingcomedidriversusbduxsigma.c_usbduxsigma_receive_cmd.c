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
struct usbduxsigma_private {int* insn_buf; } ;
struct usb_device {int dummy; } ;
struct comedi_device {struct usbduxsigma_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_TIMEOUT ; 
 int EFAULT ; 
 int RETRIES ; 
 int /*<<< orphan*/  SIZEINSNBUF ; 
 struct usb_device* comedi_to_usb_dev (struct comedi_device*) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static int usbduxsigma_receive_cmd(struct comedi_device *dev, int command)
{
	struct usb_device *usb = comedi_to_usb_dev(dev);
	struct usbduxsigma_private *devpriv = dev->private;
	int nrec;
	int ret;
	int i;

	for (i = 0; i < RETRIES; i++) {
		ret = usb_bulk_msg(usb, usb_rcvbulkpipe(usb, 8),
				   devpriv->insn_buf, SIZEINSNBUF,
				   &nrec, BULK_TIMEOUT);
		if (ret < 0)
			return ret;

		if (devpriv->insn_buf[0] == command)
			return 0;
	}
	/*
	 * This is only reached if the data has been requested a
	 * couple of times and the command was not received.
	 */
	return -EFAULT;
}