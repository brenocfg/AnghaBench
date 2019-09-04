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
typedef  int u16 ;
struct dyna_pci10xx_private {int /*<<< orphan*/  mutex; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct dyna_pci10xx_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 size_t CR_RANGE (int /*<<< orphan*/ ) ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyna_pci10xx_ai_eoc ; 
 int inw_p (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outw_p (int,scalar_t__) ; 
 unsigned int* range_codes_pci1050_ai ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dyna_pci10xx_insn_read_ai(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_insn *insn,
				     unsigned int *data)
{
	struct dyna_pci10xx_private *devpriv = dev->private;
	int n;
	u16 d = 0;
	int ret = 0;
	unsigned int chan, range;

	/* get the channel number and range */
	chan = CR_CHAN(insn->chanspec);
	range = range_codes_pci1050_ai[CR_RANGE((insn->chanspec))];

	mutex_lock(&devpriv->mutex);
	/* convert n samples */
	for (n = 0; n < insn->n; n++) {
		/* trigger conversion */
		smp_mb();
		outw_p(0x0000 + range + chan, dev->iobase + 2);
		usleep_range(10, 20);

		ret = comedi_timeout(dev, s, insn, dyna_pci10xx_ai_eoc, 0);
		if (ret)
			break;

		/* read data */
		d = inw_p(dev->iobase);
		/* mask the first 4 bits - EOC bits */
		d &= 0x0FFF;
		data[n] = d;
	}
	mutex_unlock(&devpriv->mutex);

	/* return the number of samples read/written */
	return ret ? ret : n;
}