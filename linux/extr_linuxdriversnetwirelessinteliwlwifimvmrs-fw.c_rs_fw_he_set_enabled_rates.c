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
typedef  int u16 ;
struct iwl_tlc_config_cmd {void*** ht_rates; } ;
struct ieee80211_sta_he_cap {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_mcs_80; int /*<<< orphan*/  rx_mcs_160; } ;
struct TYPE_4__ {TYPE_1__ he_mcs_nss_supp; } ;
struct ieee80211_sta {int rx_nss; TYPE_2__ he_cap; } ;

/* Variables and functions */
 int MAX_NSS ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_fw_he_ieee80211_mcs_to_rs_mcs (int) ; 

__attribute__((used)) static void
rs_fw_he_set_enabled_rates(const struct ieee80211_sta *sta,
			   const struct ieee80211_sta_he_cap *he_cap,
			   struct iwl_tlc_config_cmd *cmd)
{
	u16 mcs_160 = le16_to_cpu(sta->he_cap.he_mcs_nss_supp.rx_mcs_160);
	u16 mcs_80 = le16_to_cpu(sta->he_cap.he_mcs_nss_supp.rx_mcs_80);
	int i;

	for (i = 0; i < sta->rx_nss && i < MAX_NSS; i++) {
		u16 _mcs_160 = (mcs_160 >> (2 * i)) & 0x3;
		u16 _mcs_80 = (mcs_80 >> (2 * i)) & 0x3;

		cmd->ht_rates[i][0] =
			cpu_to_le16(rs_fw_he_ieee80211_mcs_to_rs_mcs(_mcs_80));
		cmd->ht_rates[i][1] =
			cpu_to_le16(rs_fw_he_ieee80211_mcs_to_rs_mcs(_mcs_160));
	}
}