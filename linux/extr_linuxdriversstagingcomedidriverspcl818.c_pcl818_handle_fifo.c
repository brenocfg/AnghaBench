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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; scalar_t__ iobase; } ;
struct TYPE_2__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 scalar_t__ PCL818_FI_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int inb (scalar_t__) ; 
 unsigned int pcl818_ai_get_fifo_sample (struct comedi_device*,struct comedi_subdevice*,unsigned int*) ; 
 int /*<<< orphan*/  pcl818_ai_write_sample (struct comedi_device*,struct comedi_subdevice*,unsigned int,unsigned int) ; 

__attribute__((used)) static void pcl818_handle_fifo(struct comedi_device *dev,
			       struct comedi_subdevice *s)
{
	unsigned int status;
	unsigned int chan;
	unsigned int val;
	int i, len;

	status = inb(dev->iobase + PCL818_FI_STATUS);

	if (status & 4) {
		dev_err(dev->class_dev, "A/D mode1/3 FIFO overflow!\n");
		s->async->events |= COMEDI_CB_ERROR;
		return;
	}

	if (status & 1) {
		dev_err(dev->class_dev,
			"A/D mode1/3 FIFO interrupt without data!\n");
		s->async->events |= COMEDI_CB_ERROR;
		return;
	}

	if (status & 2)
		len = 512;
	else
		len = 0;

	for (i = 0; i < len; i++) {
		val = pcl818_ai_get_fifo_sample(dev, s, &chan);
		if (!pcl818_ai_write_sample(dev, s, chan, val))
			break;
	}
}