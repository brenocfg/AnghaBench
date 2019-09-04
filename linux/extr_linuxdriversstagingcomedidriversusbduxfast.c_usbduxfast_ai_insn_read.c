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
typedef  unsigned int u16 ;
struct usbduxfast_private {int /*<<< orphan*/  mut; scalar_t__ inbuf; scalar_t__ ai_cmd_running; } ;
struct usb_device {int dummy; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct usbduxfast_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULKINEP ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 int PACKETS_TO_IGNORE ; 
 int /*<<< orphan*/  SENDADCOMMANDS ; 
 int /*<<< orphan*/  SIZEINBUF ; 
 struct usb_device* comedi_to_usb_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbduxfast_cmd_data (struct comedi_device*,int,int,int,int,int) ; 
 int usbduxfast_send_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbduxfast_ai_insn_read(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	struct usb_device *usb = comedi_to_usb_dev(dev);
	struct usbduxfast_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	u8 rngmask = range ? (0xff - 0x04) : 0xff;
	int i, j, n, actual_length;
	int ret;

	mutex_lock(&devpriv->mut);

	if (devpriv->ai_cmd_running) {
		dev_err(dev->class_dev,
			"ai_insn_read not possible, async cmd is running\n");
		mutex_unlock(&devpriv->mut);
		return -EBUSY;
	}

	/* set command for the first channel */

	/* commit data to the FIFO */
	/* data */
	usbduxfast_cmd_data(dev, 0, 0x01, 0x02, rngmask, 0x00);

	/* do the first part of the delay */
	usbduxfast_cmd_data(dev, 1, 0x0c, 0x00, 0xfe & rngmask, 0x00);
	usbduxfast_cmd_data(dev, 2, 0x01, 0x00, 0xfe & rngmask, 0x00);
	usbduxfast_cmd_data(dev, 3, 0x01, 0x00, 0xfe & rngmask, 0x00);
	usbduxfast_cmd_data(dev, 4, 0x01, 0x00, 0xfe & rngmask, 0x00);

	/* second part */
	usbduxfast_cmd_data(dev, 5, 0x0c, 0x00, rngmask, 0x00);
	usbduxfast_cmd_data(dev, 6, 0x01, 0x00, rngmask, 0x00);

	ret = usbduxfast_send_cmd(dev, SENDADCOMMANDS);
	if (ret < 0) {
		mutex_unlock(&devpriv->mut);
		return ret;
	}

	for (i = 0; i < PACKETS_TO_IGNORE; i++) {
		ret = usb_bulk_msg(usb, usb_rcvbulkpipe(usb, BULKINEP),
				   devpriv->inbuf, SIZEINBUF,
				   &actual_length, 10000);
		if (ret < 0) {
			dev_err(dev->class_dev, "insn timeout, no data\n");
			mutex_unlock(&devpriv->mut);
			return ret;
		}
	}

	for (i = 0; i < insn->n;) {
		ret = usb_bulk_msg(usb, usb_rcvbulkpipe(usb, BULKINEP),
				   devpriv->inbuf, SIZEINBUF,
				   &actual_length, 10000);
		if (ret < 0) {
			dev_err(dev->class_dev, "insn data error: %d\n", ret);
			mutex_unlock(&devpriv->mut);
			return ret;
		}
		n = actual_length / sizeof(u16);
		if ((n % 16) != 0) {
			dev_err(dev->class_dev, "insn data packet corrupted\n");
			mutex_unlock(&devpriv->mut);
			return -EINVAL;
		}
		for (j = chan; (j < n) && (i < insn->n); j = j + 16) {
			data[i] = ((u16 *)(devpriv->inbuf))[j];
			i++;
		}
	}

	mutex_unlock(&devpriv->mut);

	return insn->n;
}