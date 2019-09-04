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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ PCI173X_INT_CLR_REG ; 
 scalar_t__ PCI173X_INT_EN_REG ; 
 scalar_t__ PCI173X_INT_RF_REG ; 
 scalar_t__ PCI1750_INT_REG ; 
 scalar_t__ PCI1752_CFC_REG ; 
 scalar_t__ PCI1753E_INT_REG (int) ; 
 scalar_t__ PCI1753_INT_REG (int) ; 
 scalar_t__ PCI1754_INT_REG (int) ; 
 scalar_t__ PCI1761_INT_CLR_REG ; 
 scalar_t__ PCI1761_INT_EN_REG ; 
 scalar_t__ PCI1761_INT_RF_REG ; 
 scalar_t__ PCI1762_INT_REG ; 
#define  TYPE_PCI1730 139 
#define  TYPE_PCI1733 138 
#define  TYPE_PCI1736 137 
#define  TYPE_PCI1739 136 
#define  TYPE_PCI1750 135 
#define  TYPE_PCI1751 134 
 unsigned long TYPE_PCI1752 ; 
#define  TYPE_PCI1753 133 
#define  TYPE_PCI1753E 132 
#define  TYPE_PCI1754 131 
#define  TYPE_PCI1756 130 
#define  TYPE_PCI1761 129 
#define  TYPE_PCI1762 128 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int pci_dio_reset(struct comedi_device *dev, unsigned long cardtype)
{
	/* disable channel freeze function on the PCI-1752/1756 boards */
	if (cardtype == TYPE_PCI1752 || cardtype == TYPE_PCI1756)
		outw(0, dev->iobase + PCI1752_CFC_REG);

	/* disable and clear interrupts */
	switch (cardtype) {
	case TYPE_PCI1730:
	case TYPE_PCI1733:
	case TYPE_PCI1736:
		outb(0, dev->iobase + PCI173X_INT_EN_REG);
		outb(0x0f, dev->iobase + PCI173X_INT_CLR_REG);
		outb(0, dev->iobase + PCI173X_INT_RF_REG);
		break;
	case TYPE_PCI1739:
	case TYPE_PCI1750:
	case TYPE_PCI1751:
		outb(0x88, dev->iobase + PCI1750_INT_REG);
		break;
	case TYPE_PCI1753:
	case TYPE_PCI1753E:
		outb(0x88, dev->iobase + PCI1753_INT_REG(0));
		outb(0x80, dev->iobase + PCI1753_INT_REG(1));
		outb(0x80, dev->iobase + PCI1753_INT_REG(2));
		outb(0x80, dev->iobase + PCI1753_INT_REG(3));
		if (cardtype == TYPE_PCI1753E) {
			outb(0x88, dev->iobase + PCI1753E_INT_REG(0));
			outb(0x80, dev->iobase + PCI1753E_INT_REG(1));
			outb(0x80, dev->iobase + PCI1753E_INT_REG(2));
			outb(0x80, dev->iobase + PCI1753E_INT_REG(3));
		}
		break;
	case TYPE_PCI1754:
	case TYPE_PCI1756:
		outw(0x08, dev->iobase + PCI1754_INT_REG(0));
		outw(0x08, dev->iobase + PCI1754_INT_REG(1));
		if (cardtype == TYPE_PCI1754) {
			outw(0x08, dev->iobase + PCI1754_INT_REG(2));
			outw(0x08, dev->iobase + PCI1754_INT_REG(3));
		}
		break;
	case TYPE_PCI1761:
		/* disable interrupts */
		outb(0, dev->iobase + PCI1761_INT_EN_REG);
		/* clear interrupts */
		outb(0xff, dev->iobase + PCI1761_INT_CLR_REG);
		/* set rising edge trigger */
		outb(0, dev->iobase + PCI1761_INT_RF_REG);
		break;
	case TYPE_PCI1762:
		outw(0x0101, dev->iobase + PCI1762_INT_REG);
		break;
	default:
		break;
	}

	return 0;
}