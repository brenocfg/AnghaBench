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
struct pcmuio_private {struct pcmuio_asic* asics; } ;
struct pcmuio_asic {int /*<<< orphan*/  pagelock; } ;
struct comedi_device {struct pcmuio_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCMUIO_PAGE (int) ; 
 scalar_t__ PCMUIO_PAGE_LOCK_REG ; 
 scalar_t__ PCMUIO_PAGE_REG (int) ; 
 scalar_t__ PCMUIO_PORT_REG (int) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long pcmuio_asic_iobase (struct comedi_device*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int pcmuio_read(struct comedi_device *dev,
				int asic, int page, int port)
{
	struct pcmuio_private *devpriv = dev->private;
	struct pcmuio_asic *chip = &devpriv->asics[asic];
	unsigned long iobase = pcmuio_asic_iobase(dev, asic);
	unsigned long flags;
	unsigned int val;

	spin_lock_irqsave(&chip->pagelock, flags);
	if (page == 0) {
		/* Port registers are valid for any page */
		val = inb(iobase + PCMUIO_PORT_REG(port + 0));
		val |= (inb(iobase + PCMUIO_PORT_REG(port + 1)) << 8);
		val |= (inb(iobase + PCMUIO_PORT_REG(port + 2)) << 16);
	} else {
		outb(PCMUIO_PAGE(page), iobase + PCMUIO_PAGE_LOCK_REG);
		val = inb(iobase + PCMUIO_PAGE_REG(0));
		val |= (inb(iobase + PCMUIO_PAGE_REG(1)) << 8);
		val |= (inb(iobase + PCMUIO_PAGE_REG(2)) << 16);
	}
	spin_unlock_irqrestore(&chip->pagelock, flags);

	return val;
}