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
struct iwl_trans {TYPE_1__* cfg; int /*<<< orphan*/  hw_rev; } ;
struct TYPE_2__ {scalar_t__ device_family; int /*<<< orphan*/  integrated; } ;

/* Variables and functions */
 scalar_t__ CSR_HW_REV_STEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_MAC_SHADOW_REG_CTL2 ; 
 int /*<<< orphan*/  CSR_MAC_SHADOW_REG_CTL2_RX_WAKE ; 
 int /*<<< orphan*/  CSR_MAC_SHADOW_REG_CTRL ; 
 int /*<<< orphan*/  CSR_MAC_SHADOW_REG_CTRL_RX_WAKE ; 
 scalar_t__ IWL_DEVICE_FAMILY_9000 ; 
 scalar_t__ SILICON_A_STEP ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iwl_pcie_enable_rx_wake(struct iwl_trans *trans, bool enable)
{
	if (trans->cfg->device_family != IWL_DEVICE_FAMILY_9000)
		return;

	if (CSR_HW_REV_STEP(trans->hw_rev) != SILICON_A_STEP)
		return;

	if (!trans->cfg->integrated)
		return;

	/*
	 * Turn on the chicken-bits that cause MAC wakeup for RX-related
	 * values.
	 * This costs some power, but needed for W/A 9000 integrated A-step
	 * bug where shadow registers are not in the retention list and their
	 * value is lost when NIC powers down
	 */
	iwl_set_bit(trans, CSR_MAC_SHADOW_REG_CTRL,
		    CSR_MAC_SHADOW_REG_CTRL_RX_WAKE);
	iwl_set_bit(trans, CSR_MAC_SHADOW_REG_CTL2,
		    CSR_MAC_SHADOW_REG_CTL2_RX_WAKE);
}