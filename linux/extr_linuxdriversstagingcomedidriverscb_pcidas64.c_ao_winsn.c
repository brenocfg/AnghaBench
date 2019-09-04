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
struct pcidas64_private {unsigned int dac_control1_bits; scalar_t__ main_iobase; } ;
struct pcidas64_board {scalar_t__ layout; } ;
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct pcidas64_private* private; struct pcidas64_board* board_ptr; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAC_CONTROL0_REG ; 
 scalar_t__ DAC_CONTROL1_REG ; 
 scalar_t__ LAYOUT_4020 ; 
 scalar_t__ dac_convert_reg (int) ; 
 scalar_t__ dac_lsb_4020_reg (int) ; 
 scalar_t__ dac_msb_4020_reg (int) ; 
 int /*<<< orphan*/  set_dac_range_bits (struct comedi_device*,unsigned int*,int,int) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static int ao_winsn(struct comedi_device *dev, struct comedi_subdevice *s,
		    struct comedi_insn *insn, unsigned int *data)
{
	const struct pcidas64_board *board = dev->board_ptr;
	struct pcidas64_private *devpriv = dev->private;
	int chan = CR_CHAN(insn->chanspec);
	int range = CR_RANGE(insn->chanspec);

	/* do some initializing */
	writew(0, devpriv->main_iobase + DAC_CONTROL0_REG);

	/* set range */
	set_dac_range_bits(dev, &devpriv->dac_control1_bits, chan, range);
	writew(devpriv->dac_control1_bits,
	       devpriv->main_iobase + DAC_CONTROL1_REG);

	/* write to channel */
	if (board->layout == LAYOUT_4020) {
		writew(data[0] & 0xff,
		       devpriv->main_iobase + dac_lsb_4020_reg(chan));
		writew((data[0] >> 8) & 0xf,
		       devpriv->main_iobase + dac_msb_4020_reg(chan));
	} else {
		writew(data[0], devpriv->main_iobase + dac_convert_reg(chan));
	}

	/* remember output value */
	s->readback[chan] = data[0];

	return 1;
}