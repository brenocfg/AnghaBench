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
struct pci230_private {scalar_t__ daqio; int /*<<< orphan*/  daccon; } ;
struct comedi_subdevice {unsigned short* readback; struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct pci230_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; unsigned int chanlist_len; scalar_t__ stop_arg; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {scalar_t__ scans_done; unsigned int events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int COMEDI_CB_CANCEL_MASK ; 
 unsigned int COMEDI_CB_EOA ; 
 unsigned int COMEDI_CB_ERROR ; 
 unsigned int COMEDI_CB_OVERFLOW ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int PCI230P2_DAC_FIFOROOM_EMPTY ; 
 unsigned int PCI230P2_DAC_FIFOROOM_FULL ; 
 unsigned int PCI230P2_DAC_FIFOROOM_HALFTOFULL ; 
 unsigned int PCI230P2_DAC_FIFOROOM_ONETOHALF ; 
 unsigned short PCI230P2_DAC_FIFO_EMPTY ; 
 unsigned short PCI230P2_DAC_FIFO_FULL ; 
 unsigned short PCI230P2_DAC_FIFO_HALF ; 
 unsigned short PCI230P2_DAC_FIFO_UNDERRUN_LATCHED ; 
 int /*<<< orphan*/  PCI230P2_DAC_INT_FIFO_EMPTY ; 
 int /*<<< orphan*/  PCI230P2_DAC_INT_FIFO_MASK ; 
 scalar_t__ PCI230_DACCON ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_read_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 unsigned int comedi_nscans_left (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned short inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci230_ao_write_fifo (struct comedi_device*,unsigned short,unsigned int) ; 

__attribute__((used)) static bool pci230_handle_ao_fifo(struct comedi_device *dev,
				  struct comedi_subdevice *s)
{
	struct pci230_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int num_scans = comedi_nscans_left(s, 0);
	unsigned int room;
	unsigned short dacstat;
	unsigned int i, n;
	unsigned int events = 0;

	/* Get DAC FIFO status. */
	dacstat = inw(devpriv->daqio + PCI230_DACCON);

	if (cmd->stop_src == TRIG_COUNT && num_scans == 0)
		events |= COMEDI_CB_EOA;

	if (events == 0) {
		/* Check for FIFO underrun. */
		if (dacstat & PCI230P2_DAC_FIFO_UNDERRUN_LATCHED) {
			dev_err(dev->class_dev, "AO FIFO underrun\n");
			events |= COMEDI_CB_OVERFLOW | COMEDI_CB_ERROR;
		}
		/*
		 * Check for buffer underrun if FIFO less than half full
		 * (otherwise there will be loads of "DAC FIFO not half full"
		 * interrupts).
		 */
		if (num_scans == 0 &&
		    (dacstat & PCI230P2_DAC_FIFO_HALF) == 0) {
			dev_err(dev->class_dev, "AO buffer underrun\n");
			events |= COMEDI_CB_OVERFLOW | COMEDI_CB_ERROR;
		}
	}
	if (events == 0) {
		/* Determine how much room is in the FIFO (in samples). */
		if (dacstat & PCI230P2_DAC_FIFO_FULL)
			room = PCI230P2_DAC_FIFOROOM_FULL;
		else if (dacstat & PCI230P2_DAC_FIFO_HALF)
			room = PCI230P2_DAC_FIFOROOM_HALFTOFULL;
		else if (dacstat & PCI230P2_DAC_FIFO_EMPTY)
			room = PCI230P2_DAC_FIFOROOM_EMPTY;
		else
			room = PCI230P2_DAC_FIFOROOM_ONETOHALF;
		/* Convert room to number of scans that can be added. */
		room /= cmd->chanlist_len;
		/* Determine number of scans to process. */
		if (num_scans > room)
			num_scans = room;
		/* Process scans. */
		for (n = 0; n < num_scans; n++) {
			for (i = 0; i < cmd->chanlist_len; i++) {
				unsigned int chan = CR_CHAN(cmd->chanlist[i]);
				unsigned short datum;

				comedi_buf_read_samples(s, &datum, 1);
				pci230_ao_write_fifo(dev, datum, chan);
				s->readback[chan] = datum;
			}
		}

		if (cmd->stop_src == TRIG_COUNT &&
		    async->scans_done >= cmd->stop_arg) {
			/*
			 * All data for the command has been written
			 * to FIFO.  Set FIFO interrupt trigger level
			 * to 'empty'.
			 */
			devpriv->daccon &= ~PCI230P2_DAC_INT_FIFO_MASK;
			devpriv->daccon |= PCI230P2_DAC_INT_FIFO_EMPTY;
			outw(devpriv->daccon, devpriv->daqio + PCI230_DACCON);
		}
		/* Check if FIFO underrun occurred while writing to FIFO. */
		dacstat = inw(devpriv->daqio + PCI230_DACCON);
		if (dacstat & PCI230P2_DAC_FIFO_UNDERRUN_LATCHED) {
			dev_err(dev->class_dev, "AO FIFO underrun\n");
			events |= COMEDI_CB_OVERFLOW | COMEDI_CB_ERROR;
		}
	}
	async->events |= events;
	return !(async->events & COMEDI_CB_CANCEL_MASK);
}