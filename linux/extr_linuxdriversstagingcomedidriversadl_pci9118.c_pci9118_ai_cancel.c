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
struct pci9118_private {int ai_cfg; int ai_ctrl; int int_ctrl; scalar_t__ dma_actbuf; scalar_t__ ai_neverending; scalar_t__ ai_act_dmapos; scalar_t__ usedma; scalar_t__ ai_do; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  pacer; struct pci9118_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; } ;

/* Variables and functions */
 scalar_t__ PCI9118_AI_AUTOSCAN_MODE_REG ; 
 scalar_t__ PCI9118_AI_BURST_NUM_REG ; 
 int PCI9118_AI_CFG_PDTRG ; 
 int PCI9118_AI_CFG_PETRG ; 
 scalar_t__ PCI9118_AI_CFG_REG ; 
 scalar_t__ PCI9118_AI_CTRL_REG ; 
 scalar_t__ PCI9118_INT_CTRL_REG ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  pci9118_ai_reset_fifo (struct comedi_device*) ; 
 int /*<<< orphan*/  pci9118_amcc_dma_ena (struct comedi_device*,int) ; 
 int /*<<< orphan*/  pci9118_amcc_int_ena (struct comedi_device*,int) ; 
 int /*<<< orphan*/  pci9118_exttrg_enable (struct comedi_device*,int) ; 

__attribute__((used)) static int pci9118_ai_cancel(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	struct pci9118_private *devpriv = dev->private;

	if (devpriv->usedma)
		pci9118_amcc_dma_ena(dev, false);
	pci9118_exttrg_enable(dev, false);
	comedi_8254_pacer_enable(dev->pacer, 1, 2, false);
	/* set default config (disable burst and triggers) */
	devpriv->ai_cfg = PCI9118_AI_CFG_PDTRG | PCI9118_AI_CFG_PETRG;
	outl(devpriv->ai_cfg, dev->iobase + PCI9118_AI_CFG_REG);
	/* reset acquisition control */
	devpriv->ai_ctrl = 0;
	outl(devpriv->ai_ctrl, dev->iobase + PCI9118_AI_CTRL_REG);
	outl(0, dev->iobase + PCI9118_AI_BURST_NUM_REG);
	/* reset scan queue */
	outl(1, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_REG);
	outl(2, dev->iobase + PCI9118_AI_AUTOSCAN_MODE_REG);
	pci9118_ai_reset_fifo(dev);

	devpriv->int_ctrl = 0;
	outl(devpriv->int_ctrl, dev->iobase + PCI9118_INT_CTRL_REG);
	pci9118_amcc_int_ena(dev, false);

	devpriv->ai_do = 0;
	devpriv->usedma = 0;

	devpriv->ai_act_dmapos = 0;
	s->async->inttrig = NULL;
	devpriv->ai_neverending = 0;
	devpriv->dma_actbuf = 0;

	return 0;
}