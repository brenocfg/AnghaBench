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
struct iwl_trans_pcie {int /*<<< orphan*/  hw_init_mask; int /*<<< orphan*/  inta_mask; int /*<<< orphan*/  msix_enabled; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_INT_BIT_FH_TX ; 
 int /*<<< orphan*/  CSR_INT_MASK ; 
 int /*<<< orphan*/  CSR_MSIX_HW_INT_MASK_AD ; 
 int /*<<< orphan*/  IWL_DEBUG_ISR (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  MSIX_FH_INT_CAUSES_D2S_CH0_NUM ; 
 int /*<<< orphan*/  iwl_enable_fh_int_msk_msix (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iwl_enable_fw_load_int(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	IWL_DEBUG_ISR(trans, "Enabling FW load interrupt\n");
	if (!trans_pcie->msix_enabled) {
		trans_pcie->inta_mask = CSR_INT_BIT_FH_TX;
		iwl_write32(trans, CSR_INT_MASK, trans_pcie->inta_mask);
	} else {
		iwl_write32(trans, CSR_MSIX_HW_INT_MASK_AD,
			    trans_pcie->hw_init_mask);
		iwl_enable_fh_int_msk_msix(trans,
					   MSIX_FH_INT_CAUSES_D2S_CH0_NUM);
	}
}