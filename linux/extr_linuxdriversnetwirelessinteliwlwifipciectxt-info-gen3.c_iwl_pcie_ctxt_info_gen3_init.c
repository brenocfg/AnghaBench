#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct iwl_trans_pcie {int fw_mon_size; size_t cmd_queue; int /*<<< orphan*/  iml_dma_addr; int /*<<< orphan*/  ctxt_info_dma_addr; struct iwl_prph_scratch* prph_scratch; struct iwl_prph_info* prph_info; struct iwl_context_info_gen3* ctxt_info_gen3; TYPE_6__* rxq; TYPE_5__** txq; int /*<<< orphan*/  prph_scratch_dma_addr; int /*<<< orphan*/  prph_info_dma_addr; int /*<<< orphan*/  fw_mon_phys; } ;
struct iwl_trans {int iml_len; int /*<<< orphan*/  iml; int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {void* hwm_size; void* hwm_base_addr; } ;
struct TYPE_9__ {void* free_rbd_addr; } ;
struct TYPE_8__ {void* control_flags; } ;
struct TYPE_7__ {void* size; void* mac_id; scalar_t__ version; } ;
struct iwl_prph_scratch_ctrl_cfg {TYPE_4__ hwm_cfg; TYPE_3__ rbd_cfg; TYPE_2__ control; TYPE_1__ version; } ;
struct iwl_prph_scratch {int /*<<< orphan*/  dram; struct iwl_prph_scratch_ctrl_cfg ctrl_cfg; } ;
struct iwl_prph_info {int dummy; } ;
struct iwl_context_info_gen3 {void* mcr_size; void* mtr_size; void* mcr_base_addr; void* mtr_base_addr; void* tr_idx_arr_size; void* cr_idx_arr_size; void* cr_tail_idx_arr_base_addr; void* tr_tail_idx_arr_base_addr; void* cr_head_idx_arr_base_addr; void* prph_scratch_size; void* prph_scratch_base_addr; void* prph_info_base_addr; } ;
struct fw_img {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  used_bd_dma; int /*<<< orphan*/  cr_tail_dma; int /*<<< orphan*/  tr_tail_dma; int /*<<< orphan*/  rb_stts_dma; int /*<<< orphan*/  bd_dma; } ;
struct TYPE_11__ {int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_AUTO_FUNC_BOOT_ENA ; 
 int /*<<< orphan*/  CSR_AUTO_FUNC_INIT ; 
 int /*<<< orphan*/  CSR_CTXT_INFO_ADDR ; 
 int /*<<< orphan*/  CSR_CTXT_INFO_BOOT_CTRL ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_HW_REV ; 
 int /*<<< orphan*/  CSR_IML_DATA_ADDR ; 
 int /*<<< orphan*/  CSR_IML_SIZE_ADDR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IWL_NUM_OF_COMPLETION_RINGS ; 
 int IWL_NUM_OF_TRANSFER_RINGS ; 
 int IWL_PRPH_MTR_FORMAT_256B ; 
 int IWL_PRPH_SCRATCH_EARLY_DEBUG_EN ; 
 int IWL_PRPH_SCRATCH_EDBG_DEST_DRAM ; 
 int IWL_PRPH_SCRATCH_MTR_FORMAT ; 
 int IWL_PRPH_SCRATCH_MTR_MODE ; 
 int IWL_PRPH_SCRATCH_RB_SIZE_4K ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  MQ_RX_TABLE_SIZE ; 
 int RX_QUEUE_CB_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TFD_CMD_SLOTS ; 
 int TFD_QUEUE_CB_SIZE (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,struct iwl_prph_scratch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_enable_interrupts (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_alloc_fw_monitor (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int iwl_pcie_init_fw_sec (struct iwl_trans*,struct fw_img const*,int /*<<< orphan*/ *) ; 
 scalar_t__ iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_write64 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 

int iwl_pcie_ctxt_info_gen3_init(struct iwl_trans *trans,
				 const struct fw_img *fw)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_context_info_gen3 *ctxt_info_gen3;
	struct iwl_prph_scratch *prph_scratch;
	struct iwl_prph_scratch_ctrl_cfg *prph_sc_ctrl;
	struct iwl_prph_info *prph_info;
	void *iml_img;
	u32 control_flags = 0;
	int ret;

	/* Allocate prph scratch */
	prph_scratch = dma_alloc_coherent(trans->dev, sizeof(*prph_scratch),
					  &trans_pcie->prph_scratch_dma_addr,
					  GFP_KERNEL);
	if (!prph_scratch)
		return -ENOMEM;

	prph_sc_ctrl = &prph_scratch->ctrl_cfg;

	prph_sc_ctrl->version.version = 0;
	prph_sc_ctrl->version.mac_id =
		cpu_to_le16((u16)iwl_read32(trans, CSR_HW_REV));
	prph_sc_ctrl->version.size = cpu_to_le16(sizeof(*prph_scratch) / 4);

	control_flags = IWL_PRPH_SCRATCH_RB_SIZE_4K |
			IWL_PRPH_SCRATCH_MTR_MODE |
			(IWL_PRPH_MTR_FORMAT_256B &
			 IWL_PRPH_SCRATCH_MTR_FORMAT) |
			IWL_PRPH_SCRATCH_EARLY_DEBUG_EN |
			IWL_PRPH_SCRATCH_EDBG_DEST_DRAM;
	prph_sc_ctrl->control.control_flags = cpu_to_le32(control_flags);

	/* initialize RX default queue */
	prph_sc_ctrl->rbd_cfg.free_rbd_addr =
		cpu_to_le64(trans_pcie->rxq->bd_dma);

	/* Configure debug, for integration */
	iwl_pcie_alloc_fw_monitor(trans, 0);
	prph_sc_ctrl->hwm_cfg.hwm_base_addr =
		cpu_to_le64(trans_pcie->fw_mon_phys);
	prph_sc_ctrl->hwm_cfg.hwm_size =
		cpu_to_le32(trans_pcie->fw_mon_size);

	/* allocate ucode sections in dram and set addresses */
	ret = iwl_pcie_init_fw_sec(trans, fw, &prph_scratch->dram);
	if (ret) {
		dma_free_coherent(trans->dev,
				  sizeof(*prph_scratch),
				  prph_scratch,
				  trans_pcie->prph_scratch_dma_addr);
		return ret;
	}

	/* Allocate prph information
	 * currently we don't assign to the prph info anything, but it would get
	 * assigned later */
	prph_info = dma_alloc_coherent(trans->dev, sizeof(*prph_info),
				       &trans_pcie->prph_info_dma_addr,
				       GFP_KERNEL);
	if (!prph_info)
		return -ENOMEM;

	/* Allocate context info */
	ctxt_info_gen3 = dma_alloc_coherent(trans->dev,
					    sizeof(*ctxt_info_gen3),
					    &trans_pcie->ctxt_info_dma_addr,
					    GFP_KERNEL);
	if (!ctxt_info_gen3)
		return -ENOMEM;

	ctxt_info_gen3->prph_info_base_addr =
		cpu_to_le64(trans_pcie->prph_info_dma_addr);
	ctxt_info_gen3->prph_scratch_base_addr =
		cpu_to_le64(trans_pcie->prph_scratch_dma_addr);
	ctxt_info_gen3->prph_scratch_size =
		cpu_to_le32(sizeof(*prph_scratch));
	ctxt_info_gen3->cr_head_idx_arr_base_addr =
		cpu_to_le64(trans_pcie->rxq->rb_stts_dma);
	ctxt_info_gen3->tr_tail_idx_arr_base_addr =
		cpu_to_le64(trans_pcie->rxq->tr_tail_dma);
	ctxt_info_gen3->cr_tail_idx_arr_base_addr =
		cpu_to_le64(trans_pcie->rxq->cr_tail_dma);
	ctxt_info_gen3->cr_idx_arr_size =
		cpu_to_le16(IWL_NUM_OF_COMPLETION_RINGS);
	ctxt_info_gen3->tr_idx_arr_size =
		cpu_to_le16(IWL_NUM_OF_TRANSFER_RINGS);
	ctxt_info_gen3->mtr_base_addr =
		cpu_to_le64(trans_pcie->txq[trans_pcie->cmd_queue]->dma_addr);
	ctxt_info_gen3->mcr_base_addr =
		cpu_to_le64(trans_pcie->rxq->used_bd_dma);
	ctxt_info_gen3->mtr_size =
		cpu_to_le16(TFD_QUEUE_CB_SIZE(TFD_CMD_SLOTS));
	ctxt_info_gen3->mcr_size =
		cpu_to_le16(RX_QUEUE_CB_SIZE(MQ_RX_TABLE_SIZE));

	trans_pcie->ctxt_info_gen3 = ctxt_info_gen3;
	trans_pcie->prph_info = prph_info;
	trans_pcie->prph_scratch = prph_scratch;

	/* Allocate IML */
	iml_img = dma_alloc_coherent(trans->dev, trans->iml_len,
				     &trans_pcie->iml_dma_addr, GFP_KERNEL);
	if (!iml_img)
		return -ENOMEM;

	memcpy(iml_img, trans->iml, trans->iml_len);

	iwl_enable_interrupts(trans);

	/* kick FW self load */
	iwl_write64(trans, CSR_CTXT_INFO_ADDR,
		    trans_pcie->ctxt_info_dma_addr);
	iwl_write64(trans, CSR_IML_DATA_ADDR,
		    trans_pcie->iml_dma_addr);
	iwl_write32(trans, CSR_IML_SIZE_ADDR, trans->iml_len);
	iwl_set_bit(trans, CSR_CTXT_INFO_BOOT_CTRL, CSR_AUTO_FUNC_BOOT_ENA);
	iwl_set_bit(trans, CSR_GP_CNTRL, CSR_AUTO_FUNC_INIT);

	return 0;
}