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
struct dt282x_private {int supcsr; int ntrig; int nread; int divisor; int dacsr; int /*<<< orphan*/  dma_dir; struct comedi_isadma* dma; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_isadma {scalar_t__ cur_dma; } ;
struct comedi_device {scalar_t__ iobase; struct dt282x_private* private; } ;
struct comedi_cmd {int stop_arg; int chanlist_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_ISADMA_WRITE ; 
 int DT2821_DACSR_DACLK ; 
 int DT2821_DACSR_HBOE ; 
 int DT2821_DACSR_IDARDY ; 
 int DT2821_DACSR_LBOE ; 
 scalar_t__ DT2821_DACSR_REG ; 
 int DT2821_DACSR_SSEL ; 
 int DT2821_SUPCSR_BUFFB ; 
 int DT2821_SUPCSR_CLRDMADNE ; 
 int DT2821_SUPCSR_DACINIT ; 
 int DT2821_SUPCSR_DDMA ; 
 int DT2821_SUPCSR_DS_DA_CLK ; 
 int DT2821_SUPCSR_ERRINTEN ; 
 scalar_t__ DT2821_SUPCSR_REG ; 
 scalar_t__ DT2821_TMRCTR_REG ; 
 int /*<<< orphan*/  dt282x_ao_inttrig ; 
 int /*<<< orphan*/  dt282x_disable_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int dt282x_ao_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct dt282x_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_cmd *cmd = &s->async->cmd;

	dt282x_disable_dma(dev);

	devpriv->supcsr = DT2821_SUPCSR_ERRINTEN |
			  DT2821_SUPCSR_DS_DA_CLK |
			  DT2821_SUPCSR_DDMA;
	outw(devpriv->supcsr |
	     DT2821_SUPCSR_CLRDMADNE |
	     DT2821_SUPCSR_BUFFB |
	     DT2821_SUPCSR_DACINIT,
	     dev->iobase + DT2821_SUPCSR_REG);

	devpriv->ntrig = cmd->stop_arg * cmd->chanlist_len;
	devpriv->nread = devpriv->ntrig;

	devpriv->dma_dir = COMEDI_ISADMA_WRITE;
	dma->cur_dma = 0;

	outw(devpriv->divisor, dev->iobase + DT2821_TMRCTR_REG);

	/* clear all bits but the DIO direction bits */
	devpriv->dacsr &= (DT2821_DACSR_LBOE | DT2821_DACSR_HBOE);

	devpriv->dacsr |= (DT2821_DACSR_SSEL |
			   DT2821_DACSR_DACLK |
			   DT2821_DACSR_IDARDY);
	outw(devpriv->dacsr, dev->iobase + DT2821_DACSR_REG);

	s->async->inttrig = dt282x_ao_inttrig;

	return 0;
}