#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iwl_fw_runtime {int num_of_paging_blk; int num_of_pages_in_last_blk; TYPE_2__* trans; struct iwl_fw_paging* fw_paging_db; } ;
struct iwl_fw_paging {int fw_paging_size; int /*<<< orphan*/  fw_paging_phys; int /*<<< orphan*/  fw_paging_block; } ;
struct fw_img {int num_sec; TYPE_1__* sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ offset; int len; int data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EINVAL ; 
 int FW_PAGING_SIZE ; 
 int /*<<< orphan*/  IWL_DEBUG_FW (struct iwl_fw_runtime*,char*,int,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_fw_runtime*,char*,...) ; 
 scalar_t__ PAGING_SEPARATOR_SECTION ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_free_fw_paging (struct iwl_fw_runtime*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_fill_paging_mem(struct iwl_fw_runtime *fwrt,
			       const struct fw_img *image)
{
	int sec_idx, idx, ret;
	u32 offset = 0;

	/*
	 * find where is the paging image start point:
	 * if CPU2 exist and it's in paging format, then the image looks like:
	 * CPU1 sections (2 or more)
	 * CPU1_CPU2_SEPARATOR_SECTION delimiter - separate between CPU1 to CPU2
	 * CPU2 sections (not paged)
	 * PAGING_SEPARATOR_SECTION delimiter - separate between CPU2
	 * non paged to CPU2 paging sec
	 * CPU2 paging CSS
	 * CPU2 paging image (including instruction and data)
	 */
	for (sec_idx = 0; sec_idx < image->num_sec; sec_idx++) {
		if (image->sec[sec_idx].offset == PAGING_SEPARATOR_SECTION) {
			sec_idx++;
			break;
		}
	}

	/*
	 * If paging is enabled there should be at least 2 more sections left
	 * (one for CSS and one for Paging data)
	 */
	if (sec_idx >= image->num_sec - 1) {
		IWL_ERR(fwrt, "Paging: Missing CSS and/or paging sections\n");
		ret = -EINVAL;
		goto err;
	}

	/* copy the CSS block to the dram */
	IWL_DEBUG_FW(fwrt, "Paging: load paging CSS to FW, sec = %d\n",
		     sec_idx);

	if (image->sec[sec_idx].len > fwrt->fw_paging_db[0].fw_paging_size) {
		IWL_ERR(fwrt, "CSS block is larger than paging size\n");
		ret = -EINVAL;
		goto err;
	}

	memcpy(page_address(fwrt->fw_paging_db[0].fw_paging_block),
	       image->sec[sec_idx].data,
	       image->sec[sec_idx].len);
	dma_sync_single_for_device(fwrt->trans->dev,
				   fwrt->fw_paging_db[0].fw_paging_phys,
				   fwrt->fw_paging_db[0].fw_paging_size,
				   DMA_BIDIRECTIONAL);

	IWL_DEBUG_FW(fwrt,
		     "Paging: copied %d CSS bytes to first block\n",
		     fwrt->fw_paging_db[0].fw_paging_size);

	sec_idx++;

	/*
	 * Copy the paging blocks to the dram.  The loop index starts
	 * from 1 since the CSS block (index 0) was already copied to
	 * dram.  We use num_of_paging_blk + 1 to account for that.
	 */
	for (idx = 1; idx < fwrt->num_of_paging_blk + 1; idx++) {
		struct iwl_fw_paging *block = &fwrt->fw_paging_db[idx];
		int remaining = image->sec[sec_idx].len - offset;
		int len = block->fw_paging_size;

		/*
		 * For the last block, we copy all that is remaining,
		 * for all other blocks, we copy fw_paging_size at a
		 * time. */
		if (idx == fwrt->num_of_paging_blk) {
			len = remaining;
			if (remaining !=
			    fwrt->num_of_pages_in_last_blk * FW_PAGING_SIZE) {
				IWL_ERR(fwrt,
					"Paging: last block contains more data than expected %d\n",
					remaining);
				ret = -EINVAL;
				goto err;
			}
		} else if (block->fw_paging_size > remaining) {
			IWL_ERR(fwrt,
				"Paging: not enough data in other in block %d (%d)\n",
				idx, remaining);
			ret = -EINVAL;
			goto err;
		}

		memcpy(page_address(block->fw_paging_block),
		       image->sec[sec_idx].data + offset, len);
		dma_sync_single_for_device(fwrt->trans->dev,
					   block->fw_paging_phys,
					   block->fw_paging_size,
					   DMA_BIDIRECTIONAL);

		IWL_DEBUG_FW(fwrt,
			     "Paging: copied %d paging bytes to block %d\n",
			     len, idx);

		offset += block->fw_paging_size;
	}

	return 0;

err:
	iwl_free_fw_paging(fwrt);
	return ret;
}