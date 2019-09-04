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
 int /*<<< orphan*/  PCI1760_CMD_ENA_CNT ; 
 int /*<<< orphan*/  PCI1760_CMD_ENA_CNT_MATCH ; 
 int /*<<< orphan*/  PCI1760_CMD_ENA_CNT_OFLOW ; 
 int /*<<< orphan*/  PCI1760_CMD_ENA_FILT ; 
 int /*<<< orphan*/  PCI1760_CMD_ENA_PAT_MATCH ; 
 int /*<<< orphan*/  PCI1760_CMD_RST_CNT ; 
 int /*<<< orphan*/  PCI1760_CMD_SET_CNT (int) ; 
 int /*<<< orphan*/  PCI1760_CMD_SET_CNT_EDGE ; 
 int /*<<< orphan*/  PCI1760_CMD_SET_CNT_MATCH (int) ; 
 int /*<<< orphan*/  PCI1760_CMD_SET_PAT_MATCH ; 
 scalar_t__ PCI1760_INTCSR_REG (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci1760_cmd (struct comedi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pci1760_reset(struct comedi_device *dev)
{
	int i;

	/* disable interrupts (intcsr2 is read-only) */
	outb(0, dev->iobase + PCI1760_INTCSR_REG(0));
	outb(0, dev->iobase + PCI1760_INTCSR_REG(1));
	outb(0, dev->iobase + PCI1760_INTCSR_REG(3));

	/* disable counters */
	pci1760_cmd(dev, PCI1760_CMD_ENA_CNT, 0);

	/* disable overflow interrupts */
	pci1760_cmd(dev, PCI1760_CMD_ENA_CNT_OFLOW, 0);

	/* disable match */
	pci1760_cmd(dev, PCI1760_CMD_ENA_CNT_MATCH, 0);

	/* set match and counter reset values */
	for (i = 0; i < 8; i++) {
		pci1760_cmd(dev, PCI1760_CMD_SET_CNT_MATCH(i), 0x8000);
		pci1760_cmd(dev, PCI1760_CMD_SET_CNT(i), 0x0000);
	}

	/* reset counters to reset values */
	pci1760_cmd(dev, PCI1760_CMD_RST_CNT, 0xff);

	/* set counter count edges */
	pci1760_cmd(dev, PCI1760_CMD_SET_CNT_EDGE, 0);

	/* disable input filters */
	pci1760_cmd(dev, PCI1760_CMD_ENA_FILT, 0);

	/* disable pattern matching */
	pci1760_cmd(dev, PCI1760_CMD_ENA_PAT_MATCH, 0);

	/* set pattern match value */
	pci1760_cmd(dev, PCI1760_CMD_SET_PAT_MATCH, 0);
}