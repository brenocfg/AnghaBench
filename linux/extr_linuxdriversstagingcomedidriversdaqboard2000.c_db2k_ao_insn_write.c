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
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ DB2K_REG_DAC_SETTING (unsigned int) ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db2k_ao_eoc ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static int db2k_ao_insn_write(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	int i;

	for (i = 0; i < insn->n; i++) {
		unsigned int val = data[i];
		int ret;

		writew(val, dev->mmio + DB2K_REG_DAC_SETTING(chan));

		ret = comedi_timeout(dev, s, insn, db2k_ao_eoc, 0);
		if (ret)
			return ret;

		s->readback[chan] = val;
	}

	return insn->n;
}