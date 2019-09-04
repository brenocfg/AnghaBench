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
typedef  int u16 ;
struct il_priv {TYPE_1__* cfg; int /*<<< orphan*/  pci_dev; } ;
struct TYPE_2__ {scalar_t__ use_bsm; scalar_t__ pll_cfg_val; scalar_t__ set_l0s; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_CLK_EN_REG ; 
 int APMG_CLK_VAL_BSM_CLK_RQT ; 
 int APMG_CLK_VAL_DMA_CLK_RQT ; 
 int /*<<< orphan*/  APMG_PCIDEV_STT_REG ; 
 int /*<<< orphan*/  APMG_PCIDEV_STT_VAL_L1_ACT_DIS ; 
 int /*<<< orphan*/  CSR_ANA_PLL_CFG ; 
 int /*<<< orphan*/  CSR_DBG_HPET_MEM_REG ; 
 scalar_t__ CSR_DBG_HPET_MEM_REG_VAL ; 
 int /*<<< orphan*/  CSR_GIO_CHICKEN_BITS ; 
 scalar_t__ CSR_GIO_CHICKEN_BITS_REG_BIT_DIS_L0S_EXIT_TIMER ; 
 scalar_t__ CSR_GIO_CHICKEN_BITS_REG_BIT_L1A_NO_L0S_RX ; 
 int /*<<< orphan*/  CSR_GIO_REG ; 
 scalar_t__ CSR_GIO_REG_VAL_L0S_ENABLED ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 scalar_t__ CSR_GP_CNTRL_REG_FLAG_INIT_DONE ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 scalar_t__ CSR_HW_IF_CONFIG_REG_BIT_HAP_WAKE_L1A ; 
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  D_POWER (char*) ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int PCI_EXP_LNKCTL_ASPM_L1 ; 
 int _il_poll_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  il_clear_bit (struct il_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  il_set_bit (struct il_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  il_set_bits_prph (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_wr_prph (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcie_capability_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int
il_apm_init(struct il_priv *il)
{
	int ret = 0;
	u16 lctl;

	D_INFO("Init card's basic functions\n");

	/*
	 * Use "set_bit" below rather than "write", to preserve any hardware
	 * bits already set by default after reset.
	 */

	/* Disable L0S exit timer (platform NMI Work/Around) */
	il_set_bit(il, CSR_GIO_CHICKEN_BITS,
		   CSR_GIO_CHICKEN_BITS_REG_BIT_DIS_L0S_EXIT_TIMER);

	/*
	 * Disable L0s without affecting L1;
	 *  don't wait for ICH L0s (ICH bug W/A)
	 */
	il_set_bit(il, CSR_GIO_CHICKEN_BITS,
		   CSR_GIO_CHICKEN_BITS_REG_BIT_L1A_NO_L0S_RX);

	/* Set FH wait threshold to maximum (HW error during stress W/A) */
	il_set_bit(il, CSR_DBG_HPET_MEM_REG, CSR_DBG_HPET_MEM_REG_VAL);

	/*
	 * Enable HAP INTA (interrupt from management bus) to
	 * wake device's PCI Express link L1a -> L0s
	 * NOTE:  This is no-op for 3945 (non-existent bit)
	 */
	il_set_bit(il, CSR_HW_IF_CONFIG_REG,
		   CSR_HW_IF_CONFIG_REG_BIT_HAP_WAKE_L1A);

	/*
	 * HW bug W/A for instability in PCIe bus L0->L0S->L1 transition.
	 * Check if BIOS (or OS) enabled L1-ASPM on this device.
	 * If so (likely), disable L0S, so device moves directly L0->L1;
	 *    costs negligible amount of power savings.
	 * If not (unlikely), enable L0S, so there is at least some
	 *    power savings, even without L1.
	 */
	if (il->cfg->set_l0s) {
		pcie_capability_read_word(il->pci_dev, PCI_EXP_LNKCTL, &lctl);
		if (lctl & PCI_EXP_LNKCTL_ASPM_L1) {
			/* L1-ASPM enabled; disable(!) L0S  */
			il_set_bit(il, CSR_GIO_REG,
				   CSR_GIO_REG_VAL_L0S_ENABLED);
			D_POWER("L1 Enabled; Disabling L0S\n");
		} else {
			/* L1-ASPM disabled; enable(!) L0S */
			il_clear_bit(il, CSR_GIO_REG,
				     CSR_GIO_REG_VAL_L0S_ENABLED);
			D_POWER("L1 Disabled; Enabling L0S\n");
		}
	}

	/* Configure analog phase-lock-loop before activating to D0A */
	if (il->cfg->pll_cfg_val)
		il_set_bit(il, CSR_ANA_PLL_CFG,
			   il->cfg->pll_cfg_val);

	/*
	 * Set "initialization complete" bit to move adapter from
	 * D0U* --> D0A* (powered-up active) state.
	 */
	il_set_bit(il, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_INIT_DONE);

	/*
	 * Wait for clock stabilization; once stabilized, access to
	 * device-internal resources is supported, e.g. il_wr_prph()
	 * and accesses to uCode SRAM.
	 */
	ret =
	    _il_poll_bit(il, CSR_GP_CNTRL,
			 CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY,
			 CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY, 25000);
	if (ret < 0) {
		D_INFO("Failed to init the card\n");
		goto out;
	}

	/*
	 * Enable DMA and BSM (if used) clocks, wait for them to stabilize.
	 * BSM (Boostrap State Machine) is only in 3945 and 4965.
	 *
	 * Write to "CLK_EN_REG"; "1" bits enable clocks, while "0" bits
	 * do not disable clocks.  This preserves any hardware bits already
	 * set by default in "CLK_CTRL_REG" after reset.
	 */
	if (il->cfg->use_bsm)
		il_wr_prph(il, APMG_CLK_EN_REG,
			   APMG_CLK_VAL_DMA_CLK_RQT | APMG_CLK_VAL_BSM_CLK_RQT);
	else
		il_wr_prph(il, APMG_CLK_EN_REG, APMG_CLK_VAL_DMA_CLK_RQT);
	udelay(20);

	/* Disable L1-Active */
	il_set_bits_prph(il, APMG_PCIDEV_STT_REG,
			 APMG_PCIDEV_STT_VAL_L1_ACT_DIS);

out:
	return ret;
}