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
typedef  int u32 ;
struct iwl_mvm {TYPE_1__* fw; } ;
struct TYPE_2__ {int phy_config; } ;

/* Variables and functions */
 int FW_PHY_CFG_RX_CHAIN ; 
 int FW_PHY_CFG_RX_CHAIN_POS ; 
 int FW_PHY_CFG_TX_CHAIN ; 
 int FW_PHY_CFG_TX_CHAIN_POS ; 
 int iwl_mvm_get_valid_rx_ant (struct iwl_mvm*) ; 
 int iwl_mvm_get_valid_tx_ant (struct iwl_mvm*) ; 

__attribute__((used)) static inline u32 iwl_mvm_get_phy_config(struct iwl_mvm *mvm)
{
	u32 phy_config = ~(FW_PHY_CFG_TX_CHAIN |
			   FW_PHY_CFG_RX_CHAIN);
	u32 valid_rx_ant = iwl_mvm_get_valid_rx_ant(mvm);
	u32 valid_tx_ant = iwl_mvm_get_valid_tx_ant(mvm);

	phy_config |= valid_tx_ant << FW_PHY_CFG_TX_CHAIN_POS |
		      valid_rx_ant << FW_PHY_CFG_RX_CHAIN_POS;

	return mvm->fw->phy_config & phy_config;
}