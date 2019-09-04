#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dt282x_private {int supcsr; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; struct dt282x_private* private; } ;
struct comedi_cmd {unsigned int start_src; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ DT2821_SUPCSR_REG ; 
 int DT2821_SUPCSR_STRIG ; 
 int EINVAL ; 
 int EPIPE ; 
 int /*<<< orphan*/  dt282x_ao_setup_dma (struct comedi_device*,struct comedi_subdevice*,int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int dt282x_ao_inttrig(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     unsigned int trig_num)
{
	struct dt282x_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;

	if (trig_num != cmd->start_src)
		return -EINVAL;

	if (!dt282x_ao_setup_dma(dev, s, 0))
		return -EPIPE;

	if (!dt282x_ao_setup_dma(dev, s, 1))
		return -EPIPE;

	outw(devpriv->supcsr | DT2821_SUPCSR_STRIG,
	     dev->iobase + DT2821_SUPCSR_REG);
	s->async->inttrig = NULL;

	return 1;
}