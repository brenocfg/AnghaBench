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
struct pcmmio_private {int /*<<< orphan*/  pagelock; } ;
struct comedi_device {unsigned long iobase; struct pcmmio_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCMMIO_PAGE (int) ; 
 scalar_t__ PCMMIO_PAGE_LOCK_REG ; 
 scalar_t__ PCMMIO_PAGE_REG (int) ; 
 scalar_t__ PCMMIO_PORT_REG (int) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int pcmmio_dio_read(struct comedi_device *dev,
				    int page, int port)
{
	struct pcmmio_private *devpriv = dev->private;
	unsigned long iobase = dev->iobase;
	unsigned long flags;
	unsigned int val;

	spin_lock_irqsave(&devpriv->pagelock, flags);
	if (page == 0) {
		/* Port registers are valid for any page */
		val = inb(iobase + PCMMIO_PORT_REG(port + 0));
		val |= (inb(iobase + PCMMIO_PORT_REG(port + 1)) << 8);
		val |= (inb(iobase + PCMMIO_PORT_REG(port + 2)) << 16);
	} else {
		outb(PCMMIO_PAGE(page), iobase + PCMMIO_PAGE_LOCK_REG);
		val = inb(iobase + PCMMIO_PAGE_REG(0));
		val |= (inb(iobase + PCMMIO_PAGE_REG(1)) << 8);
		val |= (inb(iobase + PCMMIO_PAGE_REG(2)) << 16);
	}
	spin_unlock_irqrestore(&devpriv->pagelock, flags);

	return val;
}