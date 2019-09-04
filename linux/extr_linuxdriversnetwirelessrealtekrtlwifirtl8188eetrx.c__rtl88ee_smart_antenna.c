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
typedef  size_t u8 ;
struct rtl_stats {int /*<<< orphan*/  rx_pwdb_all; scalar_t__ packet_matchbssid; scalar_t__ packet_toself; } ;
struct rtl_efuse {scalar_t__ antenna_div_type; } ;
struct fast_ant_training {scalar_t__ fat_state; int antsel_rx_keep_2; int antsel_rx_keep_1; int antsel_rx_keep_0; int /*<<< orphan*/ * ant_cnt; int /*<<< orphan*/ * ant_sum; } ;
struct rtl_dm {struct fast_ant_training fat_table; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CGCS_RX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_SMART_ANTDIV ; 
 scalar_t__ FAT_TRAINING_STATE ; 
 int /*<<< orphan*/  rtl88e_dm_ant_sel_statistics (struct ieee80211_hw*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_dm* rtl_dm (int /*<<< orphan*/ ) ; 
 struct rtl_efuse* rtl_efuse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl88ee_smart_antenna(struct ieee80211_hw *hw,
	struct rtl_stats *pstatus)
{
	struct rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 antsel_tr_mux;
	struct fast_ant_training *pfat_table = &rtldm->fat_table;

	if (rtlefuse->antenna_div_type == CG_TRX_SMART_ANTDIV) {
		if (pfat_table->fat_state == FAT_TRAINING_STATE) {
			if (pstatus->packet_toself) {
				antsel_tr_mux =
					(pfat_table->antsel_rx_keep_2 << 2) |
					(pfat_table->antsel_rx_keep_1 << 1) |
					pfat_table->antsel_rx_keep_0;
				pfat_table->ant_sum[antsel_tr_mux] +=
					pstatus->rx_pwdb_all;
				pfat_table->ant_cnt[antsel_tr_mux]++;
			}
		}
	} else if ((rtlefuse->antenna_div_type == CG_TRX_HW_ANTDIV) ||
	(rtlefuse->antenna_div_type == CGCS_RX_HW_ANTDIV)) {
		if (pstatus->packet_toself || pstatus->packet_matchbssid) {
			antsel_tr_mux = (pfat_table->antsel_rx_keep_2 << 2) |
					(pfat_table->antsel_rx_keep_1 << 1) |
					pfat_table->antsel_rx_keep_0;
			rtl88e_dm_ant_sel_statistics(hw, antsel_tr_mux, 0,
						     pstatus->rx_pwdb_all);
		}

	}
}