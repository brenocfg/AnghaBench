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
struct comedi_subdevice {unsigned int maxdata; } ;
struct comedi_insn {int n; } ;
struct comedi_device {struct apci1564_private* private; } ;
struct apci1564_private {scalar_t__ timer; } ;

/* Variables and functions */
 unsigned int ADDI_TCW_CTRL_IRQ_ENA ; 
 scalar_t__ ADDI_TCW_CTRL_REG ; 
 unsigned int ADDI_TCW_CTRL_TIMER_ENA ; 
 scalar_t__ ADDI_TCW_RELOAD_REG ; 
 unsigned int ADDI_TCW_STATUS_OVERFLOW ; 
 scalar_t__ ADDI_TCW_STATUS_REG ; 
 scalar_t__ ADDI_TCW_TIMEBASE_REG ; 
 unsigned int COMEDI_COUNTER_ARMED ; 
 unsigned int COMEDI_COUNTER_COUNTING ; 
 unsigned int COMEDI_COUNTER_TERMINAL_COUNT ; 
 int EINVAL ; 
#define  INSN_CONFIG_ARM 132 
#define  INSN_CONFIG_DISARM 131 
#define  INSN_CONFIG_GET_CLOCK_SRC 130 
#define  INSN_CONFIG_GET_COUNTER_STATUS 129 
#define  INSN_CONFIG_SET_CLOCK_SRC 128 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static int apci1564_timer_insn_config(struct comedi_device *dev,
				      struct comedi_subdevice *s,
				      struct comedi_insn *insn,
				      unsigned int *data)
{
	struct apci1564_private *devpriv = dev->private;
	unsigned int val;

	switch (data[0]) {
	case INSN_CONFIG_ARM:
		if (data[1] > s->maxdata)
			return -EINVAL;
		outl(data[1], devpriv->timer + ADDI_TCW_RELOAD_REG);
		outl(ADDI_TCW_CTRL_IRQ_ENA | ADDI_TCW_CTRL_TIMER_ENA,
		     devpriv->timer + ADDI_TCW_CTRL_REG);
		break;
	case INSN_CONFIG_DISARM:
		outl(0x0, devpriv->timer + ADDI_TCW_CTRL_REG);
		break;
	case INSN_CONFIG_GET_COUNTER_STATUS:
		data[1] = 0;
		val = inl(devpriv->timer + ADDI_TCW_CTRL_REG);
		if (val & ADDI_TCW_CTRL_IRQ_ENA)
			data[1] |= COMEDI_COUNTER_ARMED;
		if (val & ADDI_TCW_CTRL_TIMER_ENA)
			data[1] |= COMEDI_COUNTER_COUNTING;
		val = inl(devpriv->timer + ADDI_TCW_STATUS_REG);
		if (val & ADDI_TCW_STATUS_OVERFLOW)
			data[1] |= COMEDI_COUNTER_TERMINAL_COUNT;
		data[2] = COMEDI_COUNTER_ARMED | COMEDI_COUNTER_COUNTING |
			  COMEDI_COUNTER_TERMINAL_COUNT;
		break;
	case INSN_CONFIG_SET_CLOCK_SRC:
		if (data[2] > s->maxdata)
			return -EINVAL;
		outl(data[1], devpriv->timer + ADDI_TCW_TIMEBASE_REG);
		outl(data[2], devpriv->timer + ADDI_TCW_RELOAD_REG);
		break;
	case INSN_CONFIG_GET_CLOCK_SRC:
		data[1] = inl(devpriv->timer + ADDI_TCW_TIMEBASE_REG);
		data[2] = inl(devpriv->timer + ADDI_TCW_RELOAD_REG);
		break;
	default:
		return -EINVAL;
	}

	return insn->n;
}