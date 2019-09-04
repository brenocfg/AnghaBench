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
struct pcmuio_private {struct pcmuio_asic* asics; } ;
struct pcmuio_asic {scalar_t__ active; scalar_t__ enabled_mask; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct pcmuio_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCMUIO_PAGE_ENAB ; 
 int pcmuio_subdevice_to_asic (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcmuio_write (struct comedi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcmuio_stop_intr(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	struct pcmuio_private *devpriv = dev->private;
	int asic = pcmuio_subdevice_to_asic(s);
	struct pcmuio_asic *chip = &devpriv->asics[asic];

	chip->enabled_mask = 0;
	chip->active = 0;
	s->async->inttrig = NULL;

	/* disable all intrs for this subdev.. */
	pcmuio_write(dev, 0, asic, PCMUIO_PAGE_ENAB, 0);
}