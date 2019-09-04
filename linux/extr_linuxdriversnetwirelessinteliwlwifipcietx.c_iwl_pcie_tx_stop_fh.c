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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_trans_pcie {int /*<<< orphan*/  irq_lock; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int FH_TCSR_CHNL_NUM ; 
 int /*<<< orphan*/  FH_TCSR_CHNL_TX_CONFIG_REG (int) ; 
 int /*<<< orphan*/  FH_TSSR_TX_STATUS_REG ; 
 int /*<<< orphan*/  FH_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE (int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int,int /*<<< orphan*/ ) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int iwl_poll_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_grab_nic_access (struct iwl_trans*,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (struct iwl_trans*,unsigned long*) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_pcie_tx_stop_fh(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	unsigned long flags;
	int ch, ret;
	u32 mask = 0;

	spin_lock(&trans_pcie->irq_lock);

	if (!iwl_trans_grab_nic_access(trans, &flags))
		goto out;

	/* Stop each Tx DMA channel */
	for (ch = 0; ch < FH_TCSR_CHNL_NUM; ch++) {
		iwl_write32(trans, FH_TCSR_CHNL_TX_CONFIG_REG(ch), 0x0);
		mask |= FH_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE(ch);
	}

	/* Wait for DMA channels to be idle */
	ret = iwl_poll_bit(trans, FH_TSSR_TX_STATUS_REG, mask, mask, 5000);
	if (ret < 0)
		IWL_ERR(trans,
			"Failing on timeout while stopping DMA channel %d [0x%08x]\n",
			ch, iwl_read32(trans, FH_TSSR_TX_STATUS_REG));

	iwl_trans_release_nic_access(trans, &flags);

out:
	spin_unlock(&trans_pcie->irq_lock);
}