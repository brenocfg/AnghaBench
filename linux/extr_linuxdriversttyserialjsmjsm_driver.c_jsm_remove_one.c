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
struct pci_dev {int device; } ;
struct jsm_board {int maxports; struct jsm_board** channels; struct jsm_board* ch_equeue; struct jsm_board* ch_rqueue; int /*<<< orphan*/  re_map_membase; int /*<<< orphan*/  irq; int /*<<< orphan*/  iobase; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_CLASSIC_4 131 
#define  PCI_DEVICE_ID_CLASSIC_4_422 130 
#define  PCI_DEVICE_ID_CLASSIC_8 129 
#define  PCI_DEVICE_ID_CLASSIC_8_422 128 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct jsm_board*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsm_remove_uart_port (struct jsm_board*) ; 
 int /*<<< orphan*/  kfree (struct jsm_board*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct jsm_board* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void jsm_remove_one(struct pci_dev *pdev)
{
	struct jsm_board *brd = pci_get_drvdata(pdev);
	int i = 0;

	switch (pdev->device) {
	case PCI_DEVICE_ID_CLASSIC_4:
	case PCI_DEVICE_ID_CLASSIC_4_422:
	case PCI_DEVICE_ID_CLASSIC_8:
	case PCI_DEVICE_ID_CLASSIC_8_422:
		/* Tell card not to interrupt anymore. */
		outb(0x0, brd->iobase + 0x4c);
		break;
	default:
		break;
	}

	jsm_remove_uart_port(brd);

	free_irq(brd->irq, brd);
	iounmap(brd->re_map_membase);

	/* Free all allocated channels structs */
	for (i = 0; i < brd->maxports; i++) {
		if (brd->channels[i]) {
			kfree(brd->channels[i]->ch_rqueue);
			kfree(brd->channels[i]->ch_equeue);
			kfree(brd->channels[i]);
		}
	}

	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kfree(brd);
}