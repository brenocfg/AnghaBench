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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  apci3xxx_ai_eoc ; 
 int apci3xxx_ai_setup (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int apci3xxx_ai_insn_read(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	int ret;
	int i;

	ret = apci3xxx_ai_setup(dev, insn->chanspec);
	if (ret)
		return ret;

	for (i = 0; i < insn->n; i++) {
		/* Start the conversion */
		writel(0x80000, dev->mmio + 8);

		/* Wait the EOS */
		ret = comedi_timeout(dev, s, insn, apci3xxx_ai_eoc, 0);
		if (ret)
			return ret;

		/* Read the analog value */
		data[i] = readl(dev->mmio + 28);
	}

	return insn->n;
}