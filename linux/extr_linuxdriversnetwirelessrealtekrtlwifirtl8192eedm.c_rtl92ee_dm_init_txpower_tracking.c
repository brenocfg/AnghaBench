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
struct rtl_priv {int dummy; } ;
struct rtl_dm {int txpower_tracking; int default_ofdm_index; int default_cck_index; int swing_idx_cck_base; int cck_index; int* swing_idx_ofdm_base; int* ofdm_index; scalar_t__* power_index_offset; scalar_t__* delta_power_index_last; scalar_t__* delta_power_index; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t MAX_RF_PATH ; 
 size_t RF90_PATH_A ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92ee_dm_init_txpower_tracking(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_dm *dm = rtl_dm(rtlpriv);
	u8 path;

	dm->txpower_tracking = true;
	dm->default_ofdm_index = 30;
	dm->default_cck_index = 20;

	dm->swing_idx_cck_base = dm->default_cck_index;
	dm->cck_index = dm->default_cck_index;

	for (path = RF90_PATH_A; path < MAX_RF_PATH; path++) {
		dm->swing_idx_ofdm_base[path] = dm->default_ofdm_index;
		dm->ofdm_index[path] = dm->default_ofdm_index;
		dm->delta_power_index[path] = 0;
		dm->delta_power_index_last[path] = 0;
		dm->power_index_offset[path] = 0;
	}
}