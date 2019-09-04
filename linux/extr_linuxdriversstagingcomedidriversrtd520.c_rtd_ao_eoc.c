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
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 unsigned int FS_DAC1_NOT_EMPTY ; 
 unsigned int FS_DAC2_NOT_EMPTY ; 
 scalar_t__ LAS0_ADC ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static int rtd_ao_eoc(struct comedi_device *dev,
		      struct comedi_subdevice *s,
		      struct comedi_insn *insn,
		      unsigned long context)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int bit = (chan == 0) ? FS_DAC1_NOT_EMPTY : FS_DAC2_NOT_EMPTY;
	unsigned int status;

	status = readl(dev->mmio + LAS0_ADC);
	if (status & bit)
		return 0;
	return -EBUSY;
}