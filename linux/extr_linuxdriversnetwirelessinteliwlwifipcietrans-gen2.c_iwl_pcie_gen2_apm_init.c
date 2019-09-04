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
struct iwl_trans {int /*<<< orphan*/  status; TYPE_2__* cfg; } ;
struct TYPE_4__ {TYPE_1__* csr; } ;
struct TYPE_3__ {int /*<<< orphan*/  flag_mac_clock_ready; int /*<<< orphan*/  flag_init_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_DBG_HPET_MEM_REG ; 
 int /*<<< orphan*/  CSR_DBG_HPET_MEM_REG_VAL ; 
 int /*<<< orphan*/  CSR_GIO_CHICKEN_BITS ; 
 int /*<<< orphan*/  CSR_GIO_CHICKEN_BITS_REG_BIT_L1A_NO_L0S_RX ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG_BIT_HAP_WAKE_L1A ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  STATUS_DEVICE_ENABLED ; 
 int /*<<< orphan*/  iwl_pcie_apm_config (struct iwl_trans*) ; 
 int iwl_poll_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_pcie_gen2_apm_init(struct iwl_trans *trans)
{
	int ret = 0;

	IWL_DEBUG_INFO(trans, "Init card's basic functions\n");

	/*
	 * Use "set_bit" below rather than "write", to preserve any hardware
	 * bits already set by default after reset.
	 */

	/*
	 * Disable L0s without affecting L1;
	 * don't wait for ICH L0s (ICH bug W/A)
	 */
	iwl_set_bit(trans, CSR_GIO_CHICKEN_BITS,
		    CSR_GIO_CHICKEN_BITS_REG_BIT_L1A_NO_L0S_RX);

	/* Set FH wait threshold to maximum (HW error during stress W/A) */
	iwl_set_bit(trans, CSR_DBG_HPET_MEM_REG, CSR_DBG_HPET_MEM_REG_VAL);

	/*
	 * Enable HAP INTA (interrupt from management bus) to
	 * wake device's PCI Express link L1a -> L0s
	 */
	iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
		    CSR_HW_IF_CONFIG_REG_BIT_HAP_WAKE_L1A);

	iwl_pcie_apm_config(trans);

	/*
	 * Set "initialization complete" bit to move adapter from
	 * D0U* --> D0A* (powered-up active) state.
	 */
	iwl_set_bit(trans, CSR_GP_CNTRL,
		    BIT(trans->cfg->csr->flag_init_done));

	/*
	 * Wait for clock stabilization; once stabilized, access to
	 * device-internal resources is supported, e.g. iwl_write_prph()
	 * and accesses to uCode SRAM.
	 */
	ret = iwl_poll_bit(trans, CSR_GP_CNTRL,
			   BIT(trans->cfg->csr->flag_mac_clock_ready),
			   BIT(trans->cfg->csr->flag_mac_clock_ready),
			   25000);
	if (ret < 0) {
		IWL_DEBUG_INFO(trans, "Failed to init the card\n");
		return ret;
	}

	set_bit(STATUS_DEVICE_ENABLED, &trans->status);

	return 0;
}