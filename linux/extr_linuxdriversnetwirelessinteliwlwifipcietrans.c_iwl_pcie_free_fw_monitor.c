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
struct iwl_trans_pcie {scalar_t__ fw_mon_size; scalar_t__ fw_mon_phys; int /*<<< orphan*/ * fw_mon_page; } ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (scalar_t__) ; 

__attribute__((used)) static void iwl_pcie_free_fw_monitor(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	if (!trans_pcie->fw_mon_page)
		return;

	dma_unmap_page(trans->dev, trans_pcie->fw_mon_phys,
		       trans_pcie->fw_mon_size, DMA_FROM_DEVICE);
	__free_pages(trans_pcie->fw_mon_page,
		     get_order(trans_pcie->fw_mon_size));
	trans_pcie->fw_mon_page = NULL;
	trans_pcie->fw_mon_phys = 0;
	trans_pcie->fw_mon_size = 0;
}