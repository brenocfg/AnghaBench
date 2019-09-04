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
struct iwl_trans {TYPE_2__* cfg; } ;
struct TYPE_4__ {TYPE_1__* csr; } ;
struct TYPE_3__ {int /*<<< orphan*/  flag_init_done; int /*<<< orphan*/  flag_mac_access_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG_PERSIST_MODE ; 
 int /*<<< orphan*/  iwl_clear_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_disable_interrupts (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_disable_ict (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_enable_rx_wake (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_pcie_set_pwr (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_pcie_synchronize_irqs (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_pcie_tx_reset (struct iwl_trans*) ; 

__attribute__((used)) static void iwl_trans_pcie_d3_suspend(struct iwl_trans *trans, bool test,
				      bool reset)
{
	if (!reset) {
		/* Enable persistence mode to avoid reset */
		iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
			    CSR_HW_IF_CONFIG_REG_PERSIST_MODE);
	}

	iwl_disable_interrupts(trans);

	/*
	 * in testing mode, the host stays awake and the
	 * hardware won't be reset (not even partially)
	 */
	if (test)
		return;

	iwl_pcie_disable_ict(trans);

	iwl_pcie_synchronize_irqs(trans);

	iwl_clear_bit(trans, CSR_GP_CNTRL,
		      BIT(trans->cfg->csr->flag_mac_access_req));
	iwl_clear_bit(trans, CSR_GP_CNTRL,
		      BIT(trans->cfg->csr->flag_init_done));

	iwl_pcie_enable_rx_wake(trans, false);

	if (reset) {
		/*
		 * reset TX queues -- some of their registers reset during S3
		 * so if we don't reset everything here the D3 image would try
		 * to execute some invalid memory upon resume
		 */
		iwl_trans_pcie_tx_reset(trans);
	}

	iwl_pcie_set_pwr(trans, true);
}