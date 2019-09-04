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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct pci_dev {int device; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
struct mid8250 {int dma_index; int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int) ; 
#define  PCI_DEVICE_ID_INTEL_PNW_UART1 130 
#define  PCI_DEVICE_ID_INTEL_PNW_UART2 129 
#define  PCI_DEVICE_ID_INTEL_PNW_UART3 128 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pnw_setup(struct mid8250 *mid, struct uart_port *p)
{
	struct pci_dev *pdev = to_pci_dev(p->dev);

	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEL_PNW_UART1:
		mid->dma_index = 0;
		break;
	case PCI_DEVICE_ID_INTEL_PNW_UART2:
		mid->dma_index = 1;
		break;
	case PCI_DEVICE_ID_INTEL_PNW_UART3:
		mid->dma_index = 2;
		break;
	default:
		return -EINVAL;
	}

	mid->dma_dev = pci_get_slot(pdev->bus,
				    PCI_DEVFN(PCI_SLOT(pdev->devfn), 3));
	return 0;
}