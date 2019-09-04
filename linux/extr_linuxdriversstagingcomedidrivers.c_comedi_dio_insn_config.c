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
struct comedi_subdevice {unsigned int io_bits; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int COMEDI_INPUT ; 
 unsigned int COMEDI_OUTPUT ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_DIO_INPUT 130 
#define  INSN_CONFIG_DIO_OUTPUT 129 
#define  INSN_CONFIG_DIO_QUERY 128 

int comedi_dio_insn_config(struct comedi_device *dev,
			   struct comedi_subdevice *s,
			   struct comedi_insn *insn,
			   unsigned int *data,
			   unsigned int mask)
{
	unsigned int chan_mask = 1 << CR_CHAN(insn->chanspec);

	if (!mask)
		mask = chan_mask;

	switch (data[0]) {
	case INSN_CONFIG_DIO_INPUT:
		s->io_bits &= ~mask;
		break;

	case INSN_CONFIG_DIO_OUTPUT:
		s->io_bits |= mask;
		break;

	case INSN_CONFIG_DIO_QUERY:
		data[1] = (s->io_bits & mask) ? COMEDI_OUTPUT : COMEDI_INPUT;
		return insn->n;

	default:
		return -EINVAL;
	}

	return 0;
}