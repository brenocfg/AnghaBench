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
struct TYPE_2__ {int /*<<< orphan*/  tx_buf_size; } ;
struct pcie_service_card {TYPE_1__ pcie; struct pci_dev* dev; } ;
struct pci_dev {int dummy; } ;
struct mwifiex_adapter {int /*<<< orphan*/  tx_buf_size; struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_pcie_alloc_buffers (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static void mwifiex_pcie_up_dev(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	struct pci_dev *pdev = card->dev;

	/* tx_buf_size might be changed to 3584 by firmware during
	 * data transfer, we should reset it to default size.
	 */
	adapter->tx_buf_size = card->pcie.tx_buf_size;

	mwifiex_pcie_alloc_buffers(adapter);

	pci_set_master(pdev);
}