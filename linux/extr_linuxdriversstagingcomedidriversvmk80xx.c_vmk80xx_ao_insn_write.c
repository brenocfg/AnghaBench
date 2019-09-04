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
struct vmk80xx_private {int model; int* usb_tx_buf; int /*<<< orphan*/  limit_sem; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct vmk80xx_private* private; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int VMK8055_AO1_REG ; 
 int VMK8055_AO2_REG ; 
 int VMK8055_CMD_WRT_AD ; 
#define  VMK8055_MODEL 128 
 int VMK8061_AO_REG ; 
 size_t VMK8061_CH_REG ; 
 int VMK8061_CMD_SET_AO ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 scalar_t__ vmk80xx_write_packet (struct comedi_device*,int) ; 

__attribute__((used)) static int vmk80xx_ao_insn_write(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	struct vmk80xx_private *devpriv = dev->private;
	int chan;
	int cmd;
	int reg;
	int n;

	down(&devpriv->limit_sem);
	chan = CR_CHAN(insn->chanspec);

	switch (devpriv->model) {
	case VMK8055_MODEL:
		cmd = VMK8055_CMD_WRT_AD;
		if (!chan)
			reg = VMK8055_AO1_REG;
		else
			reg = VMK8055_AO2_REG;
		break;
	default:		/* NOTE: avoid compiler warnings */
		cmd = VMK8061_CMD_SET_AO;
		reg = VMK8061_AO_REG;
		devpriv->usb_tx_buf[VMK8061_CH_REG] = chan;
		break;
	}

	for (n = 0; n < insn->n; n++) {
		devpriv->usb_tx_buf[reg] = data[n];

		if (vmk80xx_write_packet(dev, cmd))
			break;
	}

	up(&devpriv->limit_sem);

	return n;
}