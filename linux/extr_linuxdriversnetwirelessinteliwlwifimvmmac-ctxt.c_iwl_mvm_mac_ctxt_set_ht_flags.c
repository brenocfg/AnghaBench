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
typedef  int u8 ;
typedef  int u32 ;
struct iwl_mvm {int dummy; } ;
struct iwl_mac_ctx_cmd {int /*<<< orphan*/  protection_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  width; } ;
struct TYPE_4__ {int ht_operation_mode; TYPE_1__ chandef; } ;
struct ieee80211_vif {TYPE_2__ bss_conf; } ;

/* Variables and functions */
 int IEEE80211_HT_OP_MODE_PROTECTION ; 
#define  IEEE80211_HT_OP_MODE_PROTECTION_20MHZ 131 
#define  IEEE80211_HT_OP_MODE_PROTECTION_NONE 130 
#define  IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED 129 
#define  IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER 128 
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int MAC_PROT_FLG_FAT_PROT ; 
 int MAC_PROT_FLG_HT_PROT ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_20 ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static void iwl_mvm_mac_ctxt_set_ht_flags(struct iwl_mvm *mvm,
					 struct ieee80211_vif *vif,
					 struct iwl_mac_ctx_cmd *cmd)
{
	/* for both sta and ap, ht_operation_mode hold the protection_mode */
	u8 protection_mode = vif->bss_conf.ht_operation_mode &
				 IEEE80211_HT_OP_MODE_PROTECTION;
	/* The fw does not distinguish between ht and fat */
	u32 ht_flag = MAC_PROT_FLG_HT_PROT | MAC_PROT_FLG_FAT_PROT;

	IWL_DEBUG_RATE(mvm, "protection mode set to %d\n", protection_mode);
	/*
	 * See section 9.23.3.1 of IEEE 80211-2012.
	 * Nongreenfield HT STAs Present is not supported.
	 */
	switch (protection_mode) {
	case IEEE80211_HT_OP_MODE_PROTECTION_NONE:
		break;
	case IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER:
	case IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED:
		cmd->protection_flags |= cpu_to_le32(ht_flag);
		break;
	case IEEE80211_HT_OP_MODE_PROTECTION_20MHZ:
		/* Protect when channel wider than 20MHz */
		if (vif->bss_conf.chandef.width > NL80211_CHAN_WIDTH_20)
			cmd->protection_flags |= cpu_to_le32(ht_flag);
		break;
	default:
		IWL_ERR(mvm, "Illegal protection mode %d\n",
			protection_mode);
		break;
	}
}