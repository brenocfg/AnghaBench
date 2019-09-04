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
typedef  scalar_t__ u16 ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ S626_LP_CNTR (unsigned int) ; 
 int s626_debi_read (struct comedi_device*,scalar_t__) ; 

__attribute__((used)) static int s626_enc_insn_read(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	u16 cntr_latch_reg = S626_LP_CNTR(chan);
	int i;

	for (i = 0; i < insn->n; i++) {
		unsigned int val;

		/*
		 * Read the counter's output latch LSW/MSW.
		 * Latches on LSW read.
		 */
		val = s626_debi_read(dev, cntr_latch_reg);
		val |= (s626_debi_read(dev, cntr_latch_reg + 2) << 16);
		data[i] = val;
	}

	return insn->n;
}