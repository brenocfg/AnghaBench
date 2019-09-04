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
struct pcmmio_private {scalar_t__ active; scalar_t__ enabled_mask; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct pcmmio_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCMMIO_PAGE_ENAB ; 
 int /*<<< orphan*/  pcmmio_dio_write (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcmmio_stop_intr(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	struct pcmmio_private *devpriv = dev->private;

	devpriv->enabled_mask = 0;
	devpriv->active = 0;
	s->async->inttrig = NULL;

	/* disable all dio interrupts */
	pcmmio_dio_write(dev, 0, PCMMIO_PAGE_ENAB, 0);
}