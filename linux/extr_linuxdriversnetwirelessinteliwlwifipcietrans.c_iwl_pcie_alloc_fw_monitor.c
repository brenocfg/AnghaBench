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
typedef  scalar_t__ u32 ;
struct page {int dummy; } ;
struct iwl_trans_pcie {scalar_t__ fw_mon_size; scalar_t__ fw_mon_phys; struct page* fw_mon_page; } ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_trans*,char*,scalar_t__,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int PAGE_SIZE ; 
 scalar_t__ WARN (int,char*,int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int __GFP_COMP ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_pages (struct page*,int) ; 
 struct page* alloc_pages (int,int) ; 
 scalar_t__ dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int get_order (scalar_t__) ; 

void iwl_pcie_alloc_fw_monitor(struct iwl_trans *trans, u8 max_power)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct page *page = NULL;
	dma_addr_t phys;
	u32 size = 0;
	u8 power;

	if (!max_power) {
		/* default max_power is maximum */
		max_power = 26;
	} else {
		max_power += 11;
	}

	if (WARN(max_power > 26,
		 "External buffer size for monitor is too big %d, check the FW TLV\n",
		 max_power))
		return;

	if (trans_pcie->fw_mon_page) {
		dma_sync_single_for_device(trans->dev, trans_pcie->fw_mon_phys,
					   trans_pcie->fw_mon_size,
					   DMA_FROM_DEVICE);
		return;
	}

	phys = 0;
	for (power = max_power; power >= 11; power--) {
		int order;

		size = BIT(power);
		order = get_order(size);
		page = alloc_pages(__GFP_COMP | __GFP_NOWARN | __GFP_ZERO,
				   order);
		if (!page)
			continue;

		phys = dma_map_page(trans->dev, page, 0, PAGE_SIZE << order,
				    DMA_FROM_DEVICE);
		if (dma_mapping_error(trans->dev, phys)) {
			__free_pages(page, order);
			page = NULL;
			continue;
		}
		IWL_INFO(trans,
			 "Allocated 0x%08x bytes (order %d) for firmware monitor.\n",
			 size, order);
		break;
	}

	if (WARN_ON_ONCE(!page))
		return;

	if (power != max_power)
		IWL_ERR(trans,
			"Sorry - debug buffer is only %luK while you requested %luK\n",
			(unsigned long)BIT(power - 10),
			(unsigned long)BIT(max_power - 10));

	trans_pcie->fw_mon_page = page;
	trans_pcie->fw_mon_phys = phys;
	trans_pcie->fw_mon_size = size;
}