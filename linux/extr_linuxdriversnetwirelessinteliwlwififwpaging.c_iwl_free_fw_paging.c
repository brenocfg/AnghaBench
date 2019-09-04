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
struct iwl_fw_runtime {struct iwl_fw_paging* fw_paging_db; TYPE_1__* trans; } ;
struct iwl_fw_paging {int /*<<< orphan*/ * fw_paging_block; int /*<<< orphan*/  fw_paging_size; int /*<<< orphan*/  fw_paging_phys; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  IWL_DEBUG_FW (struct iwl_fw_runtime*,char*,int) ; 
 int NUM_OF_FW_PAGING_BLOCKS ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iwl_fw_paging*,int /*<<< orphan*/ ,int) ; 

void iwl_free_fw_paging(struct iwl_fw_runtime *fwrt)
{
	int i;

	if (!fwrt->fw_paging_db[0].fw_paging_block)
		return;

	for (i = 0; i < NUM_OF_FW_PAGING_BLOCKS; i++) {
		struct iwl_fw_paging *paging = &fwrt->fw_paging_db[i];

		if (!paging->fw_paging_block) {
			IWL_DEBUG_FW(fwrt,
				     "Paging: block %d already freed, continue to next page\n",
				     i);

			continue;
		}
		dma_unmap_page(fwrt->trans->dev, paging->fw_paging_phys,
			       paging->fw_paging_size, DMA_BIDIRECTIONAL);

		__free_pages(paging->fw_paging_block,
			     get_order(paging->fw_paging_size));
		paging->fw_paging_block = NULL;
	}

	memset(fwrt->fw_paging_db, 0, sizeof(fwrt->fw_paging_db));
}