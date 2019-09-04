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
struct pcie_service_card {int /*<<< orphan*/ * cmd_buf; int /*<<< orphan*/ * cmdrsp_buf; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_unmap_pci_memory (struct mwifiex_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_pcie_delete_cmdrsp_buf(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card;

	if (!adapter)
		return 0;

	card = adapter->card;

	if (card && card->cmdrsp_buf) {
		mwifiex_unmap_pci_memory(adapter, card->cmdrsp_buf,
					 PCI_DMA_FROMDEVICE);
		dev_kfree_skb_any(card->cmdrsp_buf);
		card->cmdrsp_buf = NULL;
	}

	if (card && card->cmd_buf) {
		mwifiex_unmap_pci_memory(adapter, card->cmd_buf,
					 PCI_DMA_TODEVICE);
		dev_kfree_skb_any(card->cmd_buf);
		card->cmd_buf = NULL;
	}
	return 0;
}