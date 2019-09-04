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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct apci1564_private* private; } ;
struct apci1564_private {unsigned long counters; } ;

/* Variables and functions */
 unsigned int ADDI_TCW_CTRL_CNTR_ENA ; 
 unsigned int ADDI_TCW_CTRL_IRQ_ENA ; 
 int /*<<< orphan*/  ADDI_TCW_CTRL_REG ; 
 int /*<<< orphan*/  ADDI_TCW_RELOAD_REG ; 
 unsigned int ADDI_TCW_STATUS_OVERFLOW ; 
 int /*<<< orphan*/  ADDI_TCW_STATUS_REG ; 
 unsigned long APCI1564_COUNTER (unsigned int) ; 
 unsigned int COMEDI_COUNTER_ARMED ; 
 unsigned int COMEDI_COUNTER_COUNTING ; 
 unsigned int COMEDI_COUNTER_TERMINAL_COUNT ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_ARM 131 
#define  INSN_CONFIG_DISARM 130 
#define  INSN_CONFIG_GET_COUNTER_STATUS 129 
#define  INSN_CONFIG_SET_COUNTER_MODE 128 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apci1564_counter_insn_config(struct comedi_device *dev,
					struct comedi_subdevice *s,
					struct comedi_insn *insn,
					unsigned int *data)
{
	struct apci1564_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned long iobase = devpriv->counters + APCI1564_COUNTER(chan);
	unsigned int val;

	switch (data[0]) {
	case INSN_CONFIG_ARM:
		val = inl(iobase + ADDI_TCW_CTRL_REG);
		val |= ADDI_TCW_CTRL_IRQ_ENA | ADDI_TCW_CTRL_CNTR_ENA;
		outl(data[1], iobase + ADDI_TCW_RELOAD_REG);
		outl(val, iobase + ADDI_TCW_CTRL_REG);
		break;
	case INSN_CONFIG_DISARM:
		val = inl(iobase + ADDI_TCW_CTRL_REG);
		val &= ~(ADDI_TCW_CTRL_IRQ_ENA | ADDI_TCW_CTRL_CNTR_ENA);
		outl(val, iobase + ADDI_TCW_CTRL_REG);
		break;
	case INSN_CONFIG_SET_COUNTER_MODE:
		/*
		 * FIXME: The counter operation is not described in the
		 * datasheet. For now just write the raw data[1] value to
		 * the control register.
		 */
		outl(data[1], iobase + ADDI_TCW_CTRL_REG);
		break;
	case INSN_CONFIG_GET_COUNTER_STATUS:
		data[1] = 0;
		val = inl(iobase + ADDI_TCW_CTRL_REG);
		if (val & ADDI_TCW_CTRL_IRQ_ENA)
			data[1] |= COMEDI_COUNTER_ARMED;
		if (val & ADDI_TCW_CTRL_CNTR_ENA)
			data[1] |= COMEDI_COUNTER_COUNTING;
		val = inl(iobase + ADDI_TCW_STATUS_REG);
		if (val & ADDI_TCW_STATUS_OVERFLOW)
			data[1] |= COMEDI_COUNTER_TERMINAL_COUNT;
		data[2] = COMEDI_COUNTER_ARMED | COMEDI_COUNTER_COUNTING |
			  COMEDI_COUNTER_TERMINAL_COUNT;
		break;
	default:
		return -EINVAL;
	}

	return insn->n;
}