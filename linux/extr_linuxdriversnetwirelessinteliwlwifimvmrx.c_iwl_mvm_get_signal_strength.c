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
typedef  int u32 ;
struct iwl_rx_phy_info {int /*<<< orphan*/  phy_flags; int /*<<< orphan*/ * non_cfg_phy; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_rx_status {int signal; int chains; int* chain_signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_STATS (struct iwl_mvm*,char*,int,int,int,int) ; 
 size_t IWL_RX_INFO_ENERGY_ANT_ABC_IDX ; 
 int IWL_RX_INFO_ENERGY_ANT_A_MSK ; 
 int IWL_RX_INFO_ENERGY_ANT_A_POS ; 
 int IWL_RX_INFO_ENERGY_ANT_B_MSK ; 
 int IWL_RX_INFO_ENERGY_ANT_B_POS ; 
 int IWL_RX_INFO_ENERGY_ANT_C_MSK ; 
 int IWL_RX_INFO_ENERGY_ANT_C_POS ; 
 int RX_RES_PHY_FLAGS_ANTENNA ; 
 int RX_RES_PHY_FLAGS_ANTENNA_POS ; 
 int S8_MIN ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 

__attribute__((used)) static void iwl_mvm_get_signal_strength(struct iwl_mvm *mvm,
					struct iwl_rx_phy_info *phy_info,
					struct ieee80211_rx_status *rx_status)
{
	int energy_a, energy_b, energy_c, max_energy;
	u32 val;

	val =
	    le32_to_cpu(phy_info->non_cfg_phy[IWL_RX_INFO_ENERGY_ANT_ABC_IDX]);
	energy_a = (val & IWL_RX_INFO_ENERGY_ANT_A_MSK) >>
						IWL_RX_INFO_ENERGY_ANT_A_POS;
	energy_a = energy_a ? -energy_a : S8_MIN;
	energy_b = (val & IWL_RX_INFO_ENERGY_ANT_B_MSK) >>
						IWL_RX_INFO_ENERGY_ANT_B_POS;
	energy_b = energy_b ? -energy_b : S8_MIN;
	energy_c = (val & IWL_RX_INFO_ENERGY_ANT_C_MSK) >>
						IWL_RX_INFO_ENERGY_ANT_C_POS;
	energy_c = energy_c ? -energy_c : S8_MIN;
	max_energy = max(energy_a, energy_b);
	max_energy = max(max_energy, energy_c);

	IWL_DEBUG_STATS(mvm, "energy In A %d B %d C %d , and max %d\n",
			energy_a, energy_b, energy_c, max_energy);

	rx_status->signal = max_energy;
	rx_status->chains = (le16_to_cpu(phy_info->phy_flags) &
				RX_RES_PHY_FLAGS_ANTENNA)
					>> RX_RES_PHY_FLAGS_ANTENNA_POS;
	rx_status->chain_signal[0] = energy_a;
	rx_status->chain_signal[1] = energy_b;
	rx_status->chain_signal[2] = energy_c;
}