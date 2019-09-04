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
struct pci_dev {int device; } ;
struct TYPE_2__ {struct pci_dev* usb_pdev; struct pci_dev* lio_pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int IDE_IRQ ; 
#define  PCI_DEVICE_ID_NS_87415 130 
#define  PCI_DEVICE_ID_NS_87560_LIO 129 
#define  PCI_DEVICE_ID_NS_87560_USB 128 
 int USB_IRQ ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ sio_dev ; 
 int /*<<< orphan*/  superio_interrupt_type ; 

int superio_fixup_irq(struct pci_dev *pcidev)
{
	int local_irq, i;

#ifdef DEBUG_SUPERIO_INIT
	int fn;
	fn = PCI_FUNC(pcidev->devfn);

	/* Verify the function number matches the expected device id. */
	if (expected_device[fn] != pcidev->device) {
		BUG();
		return -1;
	}
	printk(KERN_DEBUG "superio_fixup_irq(%s) ven 0x%x dev 0x%x from %ps\n",
		pci_name(pcidev),
		pcidev->vendor, pcidev->device,
		__builtin_return_address(0));
#endif

	for (i = 0; i < 16; i++) {
		irq_set_chip_and_handler(i, &superio_interrupt_type,
					 handle_simple_irq);
	}

	/*
	 * We don't allocate a SuperIO irq for the legacy IO function,
	 * since it is a "bridge". Instead, we will allocate irq's for
	 * each legacy device as they are initialized.
	 */

	switch(pcidev->device) {
	case PCI_DEVICE_ID_NS_87415:		/* Function 0 */
		local_irq = IDE_IRQ;
		break;
	case PCI_DEVICE_ID_NS_87560_LIO:	/* Function 1 */
		sio_dev.lio_pdev = pcidev;	/* save for superio_init() */
		return -1;
	case PCI_DEVICE_ID_NS_87560_USB:	/* Function 2 */
		sio_dev.usb_pdev = pcidev;	/* save for superio_init() */
		local_irq = USB_IRQ;
		break;
	default:
		local_irq = -1;
		BUG();
		break;
	}

	return local_irq;
}