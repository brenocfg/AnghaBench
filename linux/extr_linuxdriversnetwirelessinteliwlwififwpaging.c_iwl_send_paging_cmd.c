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
struct iwl_host_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;
struct iwl_fw_runtime {int num_of_pages_in_last_blk; int num_of_paging_blk; int /*<<< orphan*/  trans; TYPE_1__* fw_paging_db; } ;
struct iwl_fw_paging_cmd {int /*<<< orphan*/ * device_phy_addr; int /*<<< orphan*/  block_num; int /*<<< orphan*/  block_size; int /*<<< orphan*/  flags; } ;
struct fw_img {int dummy; } ;
typedef  int dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int fw_paging_phys; } ;

/* Variables and functions */
 int BLOCK_2_EXP_SIZE ; 
 int /*<<< orphan*/  FW_PAGING_BLOCK_CMD ; 
 int /*<<< orphan*/  IWL_ALWAYS_LONG_GROUP ; 
 int PAGE_2_EXP_SIZE ; 
 int PAGING_CMD_IS_ENABLED ; 
 int PAGING_CMD_IS_SECURED ; 
 int PAGING_CMD_NUM_OF_PAGES_IN_LAST_GRP_POS ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  iwl_cmd_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_trans_send_cmd (int /*<<< orphan*/ ,struct iwl_host_cmd*) ; 

__attribute__((used)) static int iwl_send_paging_cmd(struct iwl_fw_runtime *fwrt,
			       const struct fw_img *fw)
{
	struct iwl_fw_paging_cmd paging_cmd = {
		.flags = cpu_to_le32(PAGING_CMD_IS_SECURED |
				     PAGING_CMD_IS_ENABLED |
				     (fwrt->num_of_pages_in_last_blk <<
				      PAGING_CMD_NUM_OF_PAGES_IN_LAST_GRP_POS)),
		.block_size = cpu_to_le32(BLOCK_2_EXP_SIZE),
		.block_num = cpu_to_le32(fwrt->num_of_paging_blk),
	};
	struct iwl_host_cmd hcmd = {
		.id = iwl_cmd_id(FW_PAGING_BLOCK_CMD, IWL_ALWAYS_LONG_GROUP, 0),
		.len = { sizeof(paging_cmd), },
		.data = { &paging_cmd, },
	};
	int blk_idx;

	/* loop for for all paging blocks + CSS block */
	for (blk_idx = 0; blk_idx < fwrt->num_of_paging_blk + 1; blk_idx++) {
		dma_addr_t addr = fwrt->fw_paging_db[blk_idx].fw_paging_phys;
		__le32 phy_addr;

		addr = addr >> PAGE_2_EXP_SIZE;
		phy_addr = cpu_to_le32(addr);
		paging_cmd.device_phy_addr[blk_idx] = phy_addr;
	}

	return iwl_trans_send_cmd(fwrt->trans, &hcmd);
}