#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_trans {TYPE_2__* cfg; } ;
struct TYPE_6__ {int /*<<< orphan*/  flag_mac_clock_ready; int /*<<< orphan*/  flag_init_done; } ;
struct TYPE_5__ {TYPE_1__* base_params; TYPE_3__* csr; } ;
struct TYPE_4__ {scalar_t__ shadow_ram_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_PS_CTRL_REG ; 
 int /*<<< orphan*/  APMG_PS_CTRL_VAL_RESET_REQ ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_DBG_LINK_PWR_MGMT_REG ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_RESET_LINK_PWR_MGMT_DISABLED ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  iwl_clear_bits_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_poll_bit (struct iwl_trans*,int /*<<< orphan*/ ,int,int,int) ; 
 int iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_bits_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int iwl_init_otp_access(struct iwl_trans *trans)
{
	int ret;

	/* Enable 40MHz radio clock */
	iwl_write32(trans, CSR_GP_CNTRL,
		    iwl_read32(trans, CSR_GP_CNTRL) |
		    BIT(trans->cfg->csr->flag_init_done));

	/* wait for clock to be ready */
	ret = iwl_poll_bit(trans, CSR_GP_CNTRL,
			   BIT(trans->cfg->csr->flag_mac_clock_ready),
			   BIT(trans->cfg->csr->flag_mac_clock_ready),
			   25000);
	if (ret < 0) {
		IWL_ERR(trans, "Time out access OTP\n");
	} else {
		iwl_set_bits_prph(trans, APMG_PS_CTRL_REG,
				  APMG_PS_CTRL_VAL_RESET_REQ);
		udelay(5);
		iwl_clear_bits_prph(trans, APMG_PS_CTRL_REG,
				    APMG_PS_CTRL_VAL_RESET_REQ);

		/*
		 * CSR auto clock gate disable bit -
		 * this is only applicable for HW with OTP shadow RAM
		 */
		if (trans->cfg->base_params->shadow_ram_support)
			iwl_set_bit(trans, CSR_DBG_LINK_PWR_MGMT_REG,
				    CSR_RESET_LINK_PWR_MGMT_DISABLED);
	}
	return ret;
}