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
typedef  int u32 ;
typedef  int u16 ;
struct rtd_private {int fifosz; scalar_t__ ai_count; int xfer_count; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ mmio; int /*<<< orphan*/  attached; struct rtd_private* private; struct comedi_subdevice* read_subdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int FS_ADC_HEMPTY ; 
 int FS_ADC_NOT_EMPTY ; 
 int FS_ADC_NOT_FULL ; 
 int IRQM_ADC_ABOUT_CNT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ LAS0_ADC ; 
 scalar_t__ LAS0_CLEAR ; 
 scalar_t__ LAS0_IT ; 
 scalar_t__ LAS0_OVERRUN ; 
 scalar_t__ ai_read_n (struct comedi_device*,struct comedi_subdevice*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int readl (scalar_t__) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t rtd_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->read_subdev;
	struct rtd_private *devpriv = dev->private;
	u32 overrun;
	u16 status;
	u16 fifo_status;

	if (!dev->attached)
		return IRQ_NONE;

	fifo_status = readl(dev->mmio + LAS0_ADC);
	/* check for FIFO full, this automatically halts the ADC! */
	if (!(fifo_status & FS_ADC_NOT_FULL))	/* 0 -> full */
		goto xfer_abort;

	status = readw(dev->mmio + LAS0_IT);
	/* if interrupt was not caused by our board, or handled above */
	if (status == 0)
		return IRQ_HANDLED;

	if (status & IRQM_ADC_ABOUT_CNT) {	/* sample count -> read FIFO */
		/*
		 * since the priority interrupt controller may have queued
		 * a sample counter interrupt, even though we have already
		 * finished, we must handle the possibility that there is
		 * no data here
		 */
		if (!(fifo_status & FS_ADC_HEMPTY)) {
			/* FIFO half full */
			if (ai_read_n(dev, s, devpriv->fifosz / 2) < 0)
				goto xfer_abort;

			if (devpriv->ai_count == 0)
				goto xfer_done;
		} else if (devpriv->xfer_count > 0) {
			if (fifo_status & FS_ADC_NOT_EMPTY) {
				/* FIFO not empty */
				if (ai_read_n(dev, s, devpriv->xfer_count) < 0)
					goto xfer_abort;

				if (devpriv->ai_count == 0)
					goto xfer_done;
			}
		}
	}

	overrun = readl(dev->mmio + LAS0_OVERRUN) & 0xffff;
	if (overrun)
		goto xfer_abort;

	/* clear the interrupt */
	writew(status, dev->mmio + LAS0_CLEAR);
	readw(dev->mmio + LAS0_CLEAR);

	comedi_handle_events(dev, s);

	return IRQ_HANDLED;

xfer_abort:
	s->async->events |= COMEDI_CB_ERROR;

xfer_done:
	s->async->events |= COMEDI_CB_EOA;

	/* clear the interrupt */
	status = readw(dev->mmio + LAS0_IT);
	writew(status, dev->mmio + LAS0_CLEAR);
	readw(dev->mmio + LAS0_CLEAR);

	fifo_status = readl(dev->mmio + LAS0_ADC);
	overrun = readl(dev->mmio + LAS0_OVERRUN) & 0xffff;

	comedi_handle_events(dev, s);

	return IRQ_HANDLED;
}