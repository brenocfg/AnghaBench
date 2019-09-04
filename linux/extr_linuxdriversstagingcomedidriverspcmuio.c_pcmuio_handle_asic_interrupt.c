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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct comedi_subdevice* subdevices; } ;

/* Variables and functions */
 scalar_t__ PCMUIO_INT_PENDING_REG ; 
 int /*<<< orphan*/  PCMUIO_PAGE_INT_ID ; 
 int inb (scalar_t__) ; 
 unsigned long pcmuio_asic_iobase (struct comedi_device*,int) ; 
 int /*<<< orphan*/  pcmuio_handle_intr_subdev (struct comedi_device*,struct comedi_subdevice*,unsigned int) ; 
 unsigned int pcmuio_read (struct comedi_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmuio_write (struct comedi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcmuio_handle_asic_interrupt(struct comedi_device *dev, int asic)
{
	/* there are could be two asics so we can't use dev->read_subdev */
	struct comedi_subdevice *s = &dev->subdevices[asic * 2];
	unsigned long iobase = pcmuio_asic_iobase(dev, asic);
	unsigned int val;

	/* are there any interrupts pending */
	val = inb(iobase + PCMUIO_INT_PENDING_REG) & 0x07;
	if (!val)
		return 0;

	/* get, and clear, the pending interrupts */
	val = pcmuio_read(dev, asic, PCMUIO_PAGE_INT_ID, 0);
	pcmuio_write(dev, 0, asic, PCMUIO_PAGE_INT_ID, 0);

	/* handle the pending interrupts */
	pcmuio_handle_intr_subdev(dev, s, val);

	return 1;
}