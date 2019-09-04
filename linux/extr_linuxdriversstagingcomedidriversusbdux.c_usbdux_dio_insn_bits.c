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
struct usbdux_private {int /*<<< orphan*/  mut; int /*<<< orphan*/ * insn_buf; int /*<<< orphan*/ * dux_commands; } ;
struct comedi_subdevice {int /*<<< orphan*/  state; int /*<<< orphan*/  io_bits; } ;
struct comedi_insn {int n; } ;
struct comedi_device {struct usbdux_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBDUX_CMD_DIO_BITS ; 
 int /*<<< orphan*/  comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int receive_dux_commands (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int send_dux_commands (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbdux_dio_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct usbdux_private *devpriv = dev->private;
	int ret;

	mutex_lock(&devpriv->mut);

	comedi_dio_update_state(s, data);

	/* Always update the hardware. See the (*insn_config). */
	devpriv->dux_commands[1] = s->io_bits;
	devpriv->dux_commands[2] = s->state;

	/*
	 * This command also tells the firmware to return
	 * the digital input lines.
	 */
	ret = send_dux_commands(dev, USBDUX_CMD_DIO_BITS);
	if (ret < 0)
		goto dio_exit;
	ret = receive_dux_commands(dev, USBDUX_CMD_DIO_BITS);
	if (ret < 0)
		goto dio_exit;

	data[1] = le16_to_cpu(devpriv->insn_buf[1]);

dio_exit:
	mutex_unlock(&devpriv->mut);

	return ret ? ret : insn->n;
}