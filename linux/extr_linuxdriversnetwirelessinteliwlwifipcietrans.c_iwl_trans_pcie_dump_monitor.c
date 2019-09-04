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
struct iwl_trans_pcie {int fw_mon_size; scalar_t__ fw_mon_page; int /*<<< orphan*/  fw_mon_phys; } ;
struct iwl_trans {TYPE_2__* dbg_dest_tlv; TYPE_1__* cfg; int /*<<< orphan*/  dev; } ;
struct iwl_fw_error_dump_fw_mon {int /*<<< orphan*/  data; void* fw_mon_base_ptr; void* fw_mon_cycle_cnt; void* fw_mon_wr_ptr; } ;
struct iwl_fw_error_dump_data {void* len; scalar_t__ data; void* type; } ;
struct TYPE_4__ {scalar_t__ monitor_mode; int base_shift; scalar_t__ version; int /*<<< orphan*/  base_reg; int /*<<< orphan*/  wrap_count; int /*<<< orphan*/  write_ptr_reg; } ;
struct TYPE_3__ {scalar_t__ device_family; scalar_t__ smem_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ IWL_DEVICE_FAMILY_7000 ; 
 int IWL_FW_ERROR_DUMP_FW_MONITOR ; 
 int IWL_LDBG_M2S_BUF_BA_MSK ; 
 int IWL_M2S_UNIT_SIZE ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ MARBH_MODE ; 
 int MON_BUFF_BASE_ADDR ; 
 int MON_BUFF_CYCLE_CNT ; 
 int MON_BUFF_WRPTR ; 
 scalar_t__ SMEM_MODE ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int iwl_read_prph (struct iwl_trans*,int) ; 
 int iwl_trans_pci_dump_marbh_monitor (struct iwl_trans*,struct iwl_fw_error_dump_fw_mon*,int) ; 
 int /*<<< orphan*/  iwl_trans_read_mem (struct iwl_trans*,int,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_address (scalar_t__) ; 

__attribute__((used)) static u32
iwl_trans_pcie_dump_monitor(struct iwl_trans *trans,
			    struct iwl_fw_error_dump_data **data,
			    u32 monitor_len)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 len = 0;

	if ((trans_pcie->fw_mon_page &&
	     trans->cfg->device_family == IWL_DEVICE_FAMILY_7000) ||
	    trans->dbg_dest_tlv) {
		struct iwl_fw_error_dump_fw_mon *fw_mon_data;
		u32 base, write_ptr, wrap_cnt;

		/* If there was a dest TLV - use the values from there */
		if (trans->dbg_dest_tlv) {
			write_ptr =
				le32_to_cpu(trans->dbg_dest_tlv->write_ptr_reg);
			wrap_cnt = le32_to_cpu(trans->dbg_dest_tlv->wrap_count);
			base = le32_to_cpu(trans->dbg_dest_tlv->base_reg);
		} else {
			base = MON_BUFF_BASE_ADDR;
			write_ptr = MON_BUFF_WRPTR;
			wrap_cnt = MON_BUFF_CYCLE_CNT;
		}

		(*data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_FW_MONITOR);
		fw_mon_data = (void *)(*data)->data;
		fw_mon_data->fw_mon_wr_ptr =
			cpu_to_le32(iwl_read_prph(trans, write_ptr));
		fw_mon_data->fw_mon_cycle_cnt =
			cpu_to_le32(iwl_read_prph(trans, wrap_cnt));
		fw_mon_data->fw_mon_base_ptr =
			cpu_to_le32(iwl_read_prph(trans, base));

		len += sizeof(**data) + sizeof(*fw_mon_data);
		if (trans_pcie->fw_mon_page) {
			/*
			 * The firmware is now asserted, it won't write anything
			 * to the buffer. CPU can take ownership to fetch the
			 * data. The buffer will be handed back to the device
			 * before the firmware will be restarted.
			 */
			dma_sync_single_for_cpu(trans->dev,
						trans_pcie->fw_mon_phys,
						trans_pcie->fw_mon_size,
						DMA_FROM_DEVICE);
			memcpy(fw_mon_data->data,
			       page_address(trans_pcie->fw_mon_page),
			       trans_pcie->fw_mon_size);

			monitor_len = trans_pcie->fw_mon_size;
		} else if (trans->dbg_dest_tlv->monitor_mode == SMEM_MODE) {
			/*
			 * Update pointers to reflect actual values after
			 * shifting
			 */
			if (trans->dbg_dest_tlv->version) {
				base = (iwl_read_prph(trans, base) &
					IWL_LDBG_M2S_BUF_BA_MSK) <<
				       trans->dbg_dest_tlv->base_shift;
				base *= IWL_M2S_UNIT_SIZE;
				base += trans->cfg->smem_offset;
			} else {
				base = iwl_read_prph(trans, base) <<
				       trans->dbg_dest_tlv->base_shift;
			}

			iwl_trans_read_mem(trans, base, fw_mon_data->data,
					   monitor_len / sizeof(u32));
		} else if (trans->dbg_dest_tlv->monitor_mode == MARBH_MODE) {
			monitor_len =
				iwl_trans_pci_dump_marbh_monitor(trans,
								 fw_mon_data,
								 monitor_len);
		} else {
			/* Didn't match anything - output no monitor data */
			monitor_len = 0;
		}

		len += monitor_len;
		(*data)->len = cpu_to_le32(monitor_len + sizeof(*fw_mon_data));
	}

	return len;
}