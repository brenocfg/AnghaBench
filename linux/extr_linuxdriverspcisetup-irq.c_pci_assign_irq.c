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
typedef  int u8 ;
struct pci_host_bridge {int (* map_irq ) (struct pci_dev*,int,int) ;int (* swizzle_irq ) (struct pci_dev*,int*) ;} ;
struct pci_dev {int irq; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_INTERRUPT_LINE ; 
 int /*<<< orphan*/  PCI_INTERRUPT_PIN ; 
 int /*<<< orphan*/  pci_dbg (struct pci_dev*,char*,...) ; 
 struct pci_host_bridge* pci_find_host_bridge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct pci_dev*,int*) ; 
 int stub2 (struct pci_dev*,int,int) ; 

void pci_assign_irq(struct pci_dev *dev)
{
	u8 pin;
	u8 slot = -1;
	int irq = 0;
	struct pci_host_bridge *hbrg = pci_find_host_bridge(dev->bus);

	if (!(hbrg->map_irq)) {
		pci_dbg(dev, "runtime IRQ mapping not provided by arch\n");
		return;
	}

	/* If this device is not on the primary bus, we need to figure out
	   which interrupt pin it will come in on.   We know which slot it
	   will come in on 'cos that slot is where the bridge is.   Each
	   time the interrupt line passes through a PCI-PCI bridge we must
	   apply the swizzle function.  */

	pci_read_config_byte(dev, PCI_INTERRUPT_PIN, &pin);
	/* Cope with illegal. */
	if (pin > 4)
		pin = 1;

	if (pin) {
		/* Follow the chain of bridges, swizzling as we go.  */
		if (hbrg->swizzle_irq)
			slot = (*(hbrg->swizzle_irq))(dev, &pin);

		/*
		 * If a swizzling function is not used map_irq must
		 * ignore slot
		 */
		irq = (*(hbrg->map_irq))(dev, slot, pin);
		if (irq == -1)
			irq = 0;
	}
	dev->irq = irq;

	pci_dbg(dev, "assign IRQ: got %d\n", dev->irq);

	/* Always tell the device, so the driver knows what is
	   the real IRQ to use; the device does not use it. */
	pci_write_config_byte(dev, PCI_INTERRUPT_LINE, irq);
}