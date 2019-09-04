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
struct mf6x4_private {int /*<<< orphan*/  gpioc_reg; } ;
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ mmio; struct mf6x4_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ MF6X4_DAC_REG (unsigned int) ; 
 unsigned int MF6X4_GPIOC_DACEN ; 
 unsigned int MF6X4_GPIOC_LDAC ; 
 unsigned int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16 (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mf6x4_ao_insn_write(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	struct mf6x4_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int val = s->readback[chan];
	unsigned int gpioc;
	int i;

	/* Enable instantaneous update of converters outputs + Enable DACs */
	gpioc = ioread32(devpriv->gpioc_reg);
	iowrite32((gpioc & ~MF6X4_GPIOC_LDAC) | MF6X4_GPIOC_DACEN,
		  devpriv->gpioc_reg);

	for (i = 0; i < insn->n; i++) {
		val = data[i];
		iowrite16(val, dev->mmio + MF6X4_DAC_REG(chan));
	}
	s->readback[chan] = val;

	return insn->n;
}