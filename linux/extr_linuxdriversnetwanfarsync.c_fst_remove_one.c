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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct fst_card_info {int nports; scalar_t__ family; size_t card_no; int /*<<< orphan*/  tx_dma_handle_card; int /*<<< orphan*/  tx_dma_handle_host; int /*<<< orphan*/  device; int /*<<< orphan*/  rx_dma_handle_card; int /*<<< orphan*/  rx_dma_handle_host; int /*<<< orphan*/  mem; int /*<<< orphan*/  ctlmem; int /*<<< orphan*/  irq; int /*<<< orphan*/ * ports; } ;

/* Variables and functions */
 scalar_t__ FST_FAMILY_TXU ; 
 int /*<<< orphan*/  FST_MAX_MTU ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fst_card_info*) ; 
 int /*<<< orphan*/ ** fst_card_array ; 
 int /*<<< orphan*/  fst_disable_intr (struct fst_card_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fst_card_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 struct net_device* port_to_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_hdlc_device (struct net_device*) ; 

__attribute__((used)) static void
fst_remove_one(struct pci_dev *pdev)
{
	struct fst_card_info *card;
	int i;

	card = pci_get_drvdata(pdev);

	for (i = 0; i < card->nports; i++) {
		struct net_device *dev = port_to_dev(&card->ports[i]);
		unregister_hdlc_device(dev);
	}

	fst_disable_intr(card);
	free_irq(card->irq, card);

	iounmap(card->ctlmem);
	iounmap(card->mem);
	pci_release_regions(pdev);
	if (card->family == FST_FAMILY_TXU) {
		/*
		 * Free dma buffers
		 */
		pci_free_consistent(card->device, FST_MAX_MTU,
				    card->rx_dma_handle_host,
				    card->rx_dma_handle_card);
		pci_free_consistent(card->device, FST_MAX_MTU,
				    card->tx_dma_handle_host,
				    card->tx_dma_handle_card);
	}
	fst_card_array[card->card_no] = NULL;
}