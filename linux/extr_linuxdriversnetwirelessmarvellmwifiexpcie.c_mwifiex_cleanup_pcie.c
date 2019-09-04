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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {struct mwifiex_pcie_card_reg* reg; } ;
struct pcie_service_card {int /*<<< orphan*/  pci_mmap1; int /*<<< orphan*/  pci_mmap; int /*<<< orphan*/  work; TYPE_1__ pcie; struct pci_dev* dev; } ;
struct pci_dev {int dummy; } ;
struct mwifiex_pcie_card_reg {int /*<<< orphan*/  drv_rdy; int /*<<< orphan*/  fw_status; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FIRMWARE_READY_PCIE ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_pcie_free_buffers (struct mwifiex_adapter*) ; 
 int mwifiex_read_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ mwifiex_write_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 

__attribute__((used)) static void mwifiex_cleanup_pcie(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	struct pci_dev *pdev = card->dev;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;
	int ret;
	u32 fw_status;

	cancel_work_sync(&card->work);

	ret = mwifiex_read_reg(adapter, reg->fw_status, &fw_status);
	if (fw_status == FIRMWARE_READY_PCIE) {
		mwifiex_dbg(adapter, INFO,
			    "Clearing driver ready signature\n");
		if (mwifiex_write_reg(adapter, reg->drv_rdy, 0x00000000))
			mwifiex_dbg(adapter, ERROR,
				    "Failed to write driver not-ready signature\n");
	}

	pci_disable_device(pdev);

	pci_iounmap(pdev, card->pci_mmap);
	pci_iounmap(pdev, card->pci_mmap1);
	pci_release_region(pdev, 2);
	pci_release_region(pdev, 0);

	mwifiex_pcie_free_buffers(adapter);
}