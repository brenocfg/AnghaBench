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
struct pci224_private {int* ao_scan_vals; size_t* ao_scan_order; int daccon; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  class_dev; struct pci224_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; unsigned int chanlist_len; scalar_t__ scan_begin_src; int scan_begin_arg; } ;
struct TYPE_2__ {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 void* COMBINE (int,unsigned short,int) ; 
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_OVERFLOW ; 
 int CR_INVERT ; 
 scalar_t__ PCI224_DACCON ; 
#define  PCI224_DACCON_FIFOFL_EMPTY 130 
#define  PCI224_DACCON_FIFOFL_HALFTOFULL 129 
 unsigned short PCI224_DACCON_FIFOFL_MASK ; 
#define  PCI224_DACCON_FIFOFL_ONETOHALF 128 
 unsigned short PCI224_DACCON_FIFOINTR_EMPTY ; 
 int PCI224_DACCON_FIFOINTR_MASK ; 
 unsigned short PCI224_DACCON_TRIG_EXTN ; 
 unsigned short PCI224_DACCON_TRIG_EXTP ; 
 int PCI224_DACCON_TRIG_MASK ; 
 int PCI224_DACCON_TRIG_NONE ; 
 unsigned short PCI224_DACCON_TRIG_Z2CT0 ; 
 scalar_t__ PCI224_DACDATA ; 
 unsigned int PCI224_FIFO_ROOM_EMPTY ; 
 unsigned int PCI224_FIFO_ROOM_FULL ; 
 unsigned int PCI224_FIFO_ROOM_HALFTOFULL ; 
 unsigned int PCI224_FIFO_ROOM_ONETOHALF ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  comedi_buf_read_samples (struct comedi_subdevice*,int*,unsigned int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int comedi_nscans_left (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned short inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void pci224_ao_handle_fifo(struct comedi_device *dev,
				  struct comedi_subdevice *s)
{
	struct pci224_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int num_scans = comedi_nscans_left(s, 0);
	unsigned int room;
	unsigned short dacstat;
	unsigned int i, n;

	/* Determine how much room is in the FIFO (in samples). */
	dacstat = inw(dev->iobase + PCI224_DACCON);
	switch (dacstat & PCI224_DACCON_FIFOFL_MASK) {
	case PCI224_DACCON_FIFOFL_EMPTY:
		room = PCI224_FIFO_ROOM_EMPTY;
		if (cmd->stop_src == TRIG_COUNT &&
		    s->async->scans_done >= cmd->stop_arg) {
			/* FIFO empty at end of counted acquisition. */
			s->async->events |= COMEDI_CB_EOA;
			comedi_handle_events(dev, s);
			return;
		}
		break;
	case PCI224_DACCON_FIFOFL_ONETOHALF:
		room = PCI224_FIFO_ROOM_ONETOHALF;
		break;
	case PCI224_DACCON_FIFOFL_HALFTOFULL:
		room = PCI224_FIFO_ROOM_HALFTOFULL;
		break;
	default:
		room = PCI224_FIFO_ROOM_FULL;
		break;
	}
	if (room >= PCI224_FIFO_ROOM_ONETOHALF) {
		/* FIFO is less than half-full. */
		if (num_scans == 0) {
			/* Nothing left to put in the FIFO. */
			dev_err(dev->class_dev, "AO buffer underrun\n");
			s->async->events |= COMEDI_CB_OVERFLOW;
		}
	}
	/* Determine how many new scans can be put in the FIFO. */
	room /= cmd->chanlist_len;

	/* Determine how many scans to process. */
	if (num_scans > room)
		num_scans = room;

	/* Process scans. */
	for (n = 0; n < num_scans; n++) {
		comedi_buf_read_samples(s, &devpriv->ao_scan_vals[0],
					cmd->chanlist_len);
		for (i = 0; i < cmd->chanlist_len; i++) {
			outw(devpriv->ao_scan_vals[devpriv->ao_scan_order[i]],
			     dev->iobase + PCI224_DACDATA);
		}
	}
	if (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_done >= cmd->stop_arg) {
		/*
		 * Change FIFO interrupt trigger level to wait
		 * until FIFO is empty.
		 */
		devpriv->daccon = COMBINE(devpriv->daccon,
					  PCI224_DACCON_FIFOINTR_EMPTY,
					  PCI224_DACCON_FIFOINTR_MASK);
		outw(devpriv->daccon, dev->iobase + PCI224_DACCON);
	}
	if ((devpriv->daccon & PCI224_DACCON_TRIG_MASK) ==
	    PCI224_DACCON_TRIG_NONE) {
		unsigned short trig;

		/*
		 * This is the initial DAC FIFO interrupt at the
		 * start of the acquisition.  The DAC's scan trigger
		 * has been set to 'none' up until now.
		 *
		 * Now that data has been written to the FIFO, the
		 * DAC's scan trigger source can be set to the
		 * correct value.
		 *
		 * BUG: The first scan will be triggered immediately
		 * if the scan trigger source is at logic level 1.
		 */
		if (cmd->scan_begin_src == TRIG_TIMER) {
			trig = PCI224_DACCON_TRIG_Z2CT0;
		} else {
			/* cmd->scan_begin_src == TRIG_EXT */
			if (cmd->scan_begin_arg & CR_INVERT)
				trig = PCI224_DACCON_TRIG_EXTN;
			else
				trig = PCI224_DACCON_TRIG_EXTP;
		}
		devpriv->daccon =
		    COMBINE(devpriv->daccon, trig, PCI224_DACCON_TRIG_MASK);
		outw(devpriv->daccon, dev->iobase + PCI224_DACCON);
	}

	comedi_handle_events(dev, s);
}