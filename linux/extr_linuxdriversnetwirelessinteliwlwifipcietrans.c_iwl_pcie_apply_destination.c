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
struct iwl_trans_pcie {int fw_mon_size; int fw_mon_phys; } ;
struct iwl_trans {int dbg_dest_reg_num; TYPE_2__* cfg; struct iwl_fw_dbg_dest_tlv_v1* dbg_dest_tlv; } ;
struct iwl_fw_dbg_dest_tlv_v1 {scalar_t__ monitor_mode; int base_shift; int end_shift; int /*<<< orphan*/  end_reg; int /*<<< orphan*/  base_reg; TYPE_1__* reg_ops; int /*<<< orphan*/  size_power; } ;
struct TYPE_4__ {scalar_t__ device_family; } ;
struct TYPE_3__ {int op; int /*<<< orphan*/  val; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int BIT (int) ; 
#define  CSR_ASSIGN 134 
#define  CSR_CLEARBIT 133 
#define  CSR_SETBIT 132 
 scalar_t__ EXTERNAL_MODE ; 
 scalar_t__ IWL_DEVICE_FAMILY_8000 ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int,...) ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_trans*,char*,int /*<<< orphan*/ ) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_trans*,char*) ; 
#define  PRPH_ASSIGN 131 
#define  PRPH_BLOCKBIT 130 
#define  PRPH_CLEARBIT 129 
#define  PRPH_SETBIT 128 
 int /*<<< orphan*/  get_fw_dbg_mode_string (scalar_t__) ; 
 int /*<<< orphan*/  iwl_clear_bit (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_clear_bits_prph (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_pcie_alloc_fw_monitor (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int iwl_read_prph (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_set_bits_prph (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

void iwl_pcie_apply_destination(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	const struct iwl_fw_dbg_dest_tlv_v1 *dest = trans->dbg_dest_tlv;
	int i;

	IWL_INFO(trans, "Applying debug destination %s\n",
		 get_fw_dbg_mode_string(dest->monitor_mode));

	if (dest->monitor_mode == EXTERNAL_MODE)
		iwl_pcie_alloc_fw_monitor(trans, dest->size_power);
	else
		IWL_WARN(trans, "PCI should have external buffer debug\n");

	for (i = 0; i < trans->dbg_dest_reg_num; i++) {
		u32 addr = le32_to_cpu(dest->reg_ops[i].addr);
		u32 val = le32_to_cpu(dest->reg_ops[i].val);

		switch (dest->reg_ops[i].op) {
		case CSR_ASSIGN:
			iwl_write32(trans, addr, val);
			break;
		case CSR_SETBIT:
			iwl_set_bit(trans, addr, BIT(val));
			break;
		case CSR_CLEARBIT:
			iwl_clear_bit(trans, addr, BIT(val));
			break;
		case PRPH_ASSIGN:
			iwl_write_prph(trans, addr, val);
			break;
		case PRPH_SETBIT:
			iwl_set_bits_prph(trans, addr, BIT(val));
			break;
		case PRPH_CLEARBIT:
			iwl_clear_bits_prph(trans, addr, BIT(val));
			break;
		case PRPH_BLOCKBIT:
			if (iwl_read_prph(trans, addr) & BIT(val)) {
				IWL_ERR(trans,
					"BIT(%u) in address 0x%x is 1, stopping FW configuration\n",
					val, addr);
				goto monitor;
			}
			break;
		default:
			IWL_ERR(trans, "FW debug - unknown OP %d\n",
				dest->reg_ops[i].op);
			break;
		}
	}

monitor:
	if (dest->monitor_mode == EXTERNAL_MODE && trans_pcie->fw_mon_size) {
		iwl_write_prph(trans, le32_to_cpu(dest->base_reg),
			       trans_pcie->fw_mon_phys >> dest->base_shift);
		if (trans->cfg->device_family >= IWL_DEVICE_FAMILY_8000)
			iwl_write_prph(trans, le32_to_cpu(dest->end_reg),
				       (trans_pcie->fw_mon_phys +
					trans_pcie->fw_mon_size - 256) >>
						dest->end_shift);
		else
			iwl_write_prph(trans, le32_to_cpu(dest->end_reg),
				       (trans_pcie->fw_mon_phys +
					trans_pcie->fw_mon_size) >>
						dest->end_shift);
	}
}