#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int count; struct dt9812_usb_cmd* address; } ;
struct TYPE_6__ {TYPE_1__ read_multi_info; } ;
struct dt9812_usb_cmd {TYPE_2__ u; int /*<<< orphan*/  cmd; } ;
typedef  struct dt9812_usb_cmd u8 ;
struct usb_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct dt9812_private {TYPE_4__ cmd_rd; TYPE_3__ cmd_wr; } ;
struct comedi_device {struct dt9812_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT9812_R_MULTI_BYTE_REG ; 
 int /*<<< orphan*/  DT9812_USB_TIMEOUT ; 
 struct usb_device* comedi_to_usb_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,struct dt9812_usb_cmd*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dt9812_read_multiple_registers(struct comedi_device *dev,
					  int reg_count, u8 *address,
					  u8 *value)
{
	struct usb_device *usb = comedi_to_usb_dev(dev);
	struct dt9812_private *devpriv = dev->private;
	struct dt9812_usb_cmd cmd;
	int i, count, ret;

	cmd.cmd = cpu_to_le32(DT9812_R_MULTI_BYTE_REG);
	cmd.u.read_multi_info.count = reg_count;
	for (i = 0; i < reg_count; i++)
		cmd.u.read_multi_info.address[i] = address[i];

	/* DT9812 only responds to 32 byte writes!! */
	ret = usb_bulk_msg(usb, usb_sndbulkpipe(usb, devpriv->cmd_wr.addr),
			   &cmd, 32, &count, DT9812_USB_TIMEOUT);
	if (ret)
		return ret;

	return usb_bulk_msg(usb, usb_rcvbulkpipe(usb, devpriv->cmd_rd.addr),
			    value, reg_count, &count, DT9812_USB_TIMEOUT);
}