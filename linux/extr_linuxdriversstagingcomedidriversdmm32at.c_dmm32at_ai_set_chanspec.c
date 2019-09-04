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
struct comedi_subdevice {unsigned int n_chan; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 scalar_t__ DMM32AT_AI_CFG_REG ; 
 scalar_t__ DMM32AT_AI_HI_CHAN_REG ; 
 scalar_t__ DMM32AT_AI_LO_CHAN_REG ; 
 unsigned int DMM32AT_FIFO_CTRL_FIFORST ; 
 scalar_t__ DMM32AT_FIFO_CTRL_REG ; 
 unsigned int DMM32AT_FIFO_CTRL_SCANEN ; 
 unsigned int* dmm32at_rangebits ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void dmm32at_ai_set_chanspec(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    unsigned int chanspec, int nchan)
{
	unsigned int chan = CR_CHAN(chanspec);
	unsigned int range = CR_RANGE(chanspec);
	unsigned int last_chan = (chan + nchan - 1) % s->n_chan;

	outb(DMM32AT_FIFO_CTRL_FIFORST, dev->iobase + DMM32AT_FIFO_CTRL_REG);

	if (nchan > 1)
		outb(DMM32AT_FIFO_CTRL_SCANEN,
		     dev->iobase + DMM32AT_FIFO_CTRL_REG);

	outb(chan, dev->iobase + DMM32AT_AI_LO_CHAN_REG);
	outb(last_chan, dev->iobase + DMM32AT_AI_HI_CHAN_REG);
	outb(dmm32at_rangebits[range], dev->iobase + DMM32AT_AI_CFG_REG);
}