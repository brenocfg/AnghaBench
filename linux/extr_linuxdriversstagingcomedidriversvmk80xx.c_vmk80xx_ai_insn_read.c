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
struct vmk80xx_private {int model; int* usb_tx_buf; unsigned int* usb_rx_buf; int /*<<< orphan*/  limit_sem; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct vmk80xx_private* private; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int VMK8055_AI1_REG ; 
 int VMK8055_AI2_REG ; 
#define  VMK8055_MODEL 129 
 int VMK8061_AI_REG1 ; 
 int VMK8061_AI_REG2 ; 
 size_t VMK8061_CH_REG ; 
 int VMK8061_CMD_RD_AI ; 
#define  VMK8061_MODEL 128 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 scalar_t__ vmk80xx_read_packet (struct comedi_device*) ; 

__attribute__((used)) static int vmk80xx_ai_insn_read(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct vmk80xx_private *devpriv = dev->private;
	int chan;
	int reg[2];
	int n;

	down(&devpriv->limit_sem);
	chan = CR_CHAN(insn->chanspec);

	switch (devpriv->model) {
	case VMK8055_MODEL:
		if (!chan)
			reg[0] = VMK8055_AI1_REG;
		else
			reg[0] = VMK8055_AI2_REG;
		break;
	case VMK8061_MODEL:
	default:
		reg[0] = VMK8061_AI_REG1;
		reg[1] = VMK8061_AI_REG2;
		devpriv->usb_tx_buf[0] = VMK8061_CMD_RD_AI;
		devpriv->usb_tx_buf[VMK8061_CH_REG] = chan;
		break;
	}

	for (n = 0; n < insn->n; n++) {
		if (vmk80xx_read_packet(dev))
			break;

		if (devpriv->model == VMK8055_MODEL) {
			data[n] = devpriv->usb_rx_buf[reg[0]];
			continue;
		}

		/* VMK8061_MODEL */
		data[n] = devpriv->usb_rx_buf[reg[0]] + 256 *
		    devpriv->usb_rx_buf[reg[1]];
	}

	up(&devpriv->limit_sem);

	return n;
}