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
struct pcl812_private {int mode_reg_int; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct pcl812_private* private; } ;

/* Variables and functions */
 int PCL812_CTRL_DISABLE_TRIG ; 
 scalar_t__ PCL812_CTRL_REG ; 
 int PCL812_CTRL_SOFT_TRIG ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  pcl812_ai_clear_eoc (struct comedi_device*) ; 
 int /*<<< orphan*/  pcl812_ai_eoc ; 
 unsigned int pcl812_ai_get_sample (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcl812_ai_set_chan_range (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcl812_ai_soft_trig (struct comedi_device*) ; 

__attribute__((used)) static int pcl812_ai_insn_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	struct pcl812_private *devpriv = dev->private;
	int ret = 0;
	int i;

	outb(devpriv->mode_reg_int | PCL812_CTRL_SOFT_TRIG,
	     dev->iobase + PCL812_CTRL_REG);

	pcl812_ai_set_chan_range(dev, insn->chanspec, 1);

	for (i = 0; i < insn->n; i++) {
		pcl812_ai_clear_eoc(dev);
		pcl812_ai_soft_trig(dev);

		ret = comedi_timeout(dev, s, insn, pcl812_ai_eoc, 0);
		if (ret)
			break;

		data[i] = pcl812_ai_get_sample(dev, s);
	}
	outb(devpriv->mode_reg_int | PCL812_CTRL_DISABLE_TRIG,
	     dev->iobase + PCL812_CTRL_REG);
	pcl812_ai_clear_eoc(dev);

	return ret ? ret : insn->n;
}