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
struct pci224_private {unsigned short daccon; } ;
struct pci224_board {int ao_bits; int /*<<< orphan*/ * ao_hwrange; } ;
struct comedi_device {scalar_t__ iobase; struct pci224_private* private; struct pci224_board* board_ptr; } ;

/* Variables and functions */
 unsigned short COMBINE (unsigned short,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PCI224_DACCEN ; 
 scalar_t__ PCI224_DACCON ; 
 unsigned short PCI224_DACCON_FIFORESET ; 
 int PCI224_DACCON_POLAR_BI ; 
 int PCI224_DACCON_POLAR_MASK ; 
 int PCI224_DACCON_VREF_MASK ; 
 scalar_t__ PCI224_DACDATA ; 
 scalar_t__ PCI224_SOFTTRIG ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 

__attribute__((used)) static void
pci224_ao_set_data(struct comedi_device *dev, int chan, int range,
		   unsigned int data)
{
	const struct pci224_board *board = dev->board_ptr;
	struct pci224_private *devpriv = dev->private;
	unsigned short mangled;

	/* Enable the channel. */
	outw(1 << chan, dev->iobase + PCI224_DACCEN);
	/* Set range and reset FIFO. */
	devpriv->daccon = COMBINE(devpriv->daccon, board->ao_hwrange[range],
				  PCI224_DACCON_POLAR_MASK |
				  PCI224_DACCON_VREF_MASK);
	outw(devpriv->daccon | PCI224_DACCON_FIFORESET,
	     dev->iobase + PCI224_DACCON);
	/*
	 * Mangle the data.  The hardware expects:
	 * - bipolar: 16-bit 2's complement
	 * - unipolar: 16-bit unsigned
	 */
	mangled = (unsigned short)data << (16 - board->ao_bits);
	if ((devpriv->daccon & PCI224_DACCON_POLAR_MASK) ==
	    PCI224_DACCON_POLAR_BI) {
		mangled ^= 0x8000;
	}
	/* Write mangled data to the FIFO. */
	outw(mangled, dev->iobase + PCI224_DACDATA);
	/* Trigger the conversion. */
	inw(dev->iobase + PCI224_SOFTTRIG);
}