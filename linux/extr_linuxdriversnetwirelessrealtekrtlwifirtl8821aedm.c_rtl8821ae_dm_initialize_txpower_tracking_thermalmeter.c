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
typedef  int u8 ;
struct TYPE_2__ {int txpower_track_control; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct rtl_efuse {int /*<<< orphan*/  eeprom_thermalmeter; } ;
struct rtl_dm {int default_ofdm_index; int default_cck_index; int swing_idx_cck_base; int cck_index; int* swing_idx_ofdm_base; int* ofdm_index; scalar_t__* delta_power_index_last; scalar_t__* power_index_offset; scalar_t__* delta_power_index; int /*<<< orphan*/  thermalvalue_lck; int /*<<< orphan*/  thermalvalue_iqk; int /*<<< orphan*/  thermalvalue; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int MAX_RF_PATH ; 
 int RF90_PATH_A ; 
 int TXSCALE_TABLE_SIZE ; 
 int rtl8821ae_dm_get_swing_index (struct ieee80211_hw*) ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8821ae_dm_initialize_txpower_tracking_thermalmeter(
				struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_dm *rtldm = rtl_dm(rtlpriv);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);
	u8 default_swing_index  = 0;
	u8 p = 0;

	rtlpriv->dm.txpower_track_control = true;
	rtldm->thermalvalue = rtlefuse->eeprom_thermalmeter;
	rtldm->thermalvalue_iqk = rtlefuse->eeprom_thermalmeter;
	rtldm->thermalvalue_lck = rtlefuse->eeprom_thermalmeter;
	default_swing_index = rtl8821ae_dm_get_swing_index(hw);

	rtldm->default_ofdm_index =
		(default_swing_index == TXSCALE_TABLE_SIZE) ?
		24 : default_swing_index;
	rtldm->default_cck_index = 24;

	rtldm->swing_idx_cck_base = rtldm->default_cck_index;
	rtldm->cck_index = rtldm->default_cck_index;

	for (p = RF90_PATH_A; p < MAX_RF_PATH; ++p) {
		rtldm->swing_idx_ofdm_base[p] =
			rtldm->default_ofdm_index;
		rtldm->ofdm_index[p] = rtldm->default_ofdm_index;
		rtldm->delta_power_index[p] = 0;
		rtldm->power_index_offset[p] = 0;
		rtldm->delta_power_index_last[p] = 0;
	}
}