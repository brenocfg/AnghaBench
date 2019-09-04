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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_hal {scalar_t__ current_bandtype; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 int /*<<< orphan*/  _rtl8822be_phy_set_txpower_level_by_path (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cck_rates ; 
 int /*<<< orphan*/  ht_rates_1t ; 
 int /*<<< orphan*/  ht_rates_2t ; 
 int /*<<< orphan*/  ofdm_rates ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  sizes_of_cck_retes ; 
 int /*<<< orphan*/  sizes_of_ht_retes_1t ; 
 int /*<<< orphan*/  sizes_of_ht_retes_2t ; 
 int /*<<< orphan*/  sizes_of_ofdm_retes ; 
 int /*<<< orphan*/  sizes_of_vht_retes ; 
 int /*<<< orphan*/  vht_rates_1t ; 
 int /*<<< orphan*/  vht_rates_2t ; 

void rtl8822be_phy_set_txpower_level_by_path(struct ieee80211_hw *hw,
					     u8 channel, u8 path)
{
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	/*
	 * Below order is *VERY* important!
	 * Because _rtl8822be_phy_set_txpower_index() do actually writing
	 * every four power values.
	 */
	if (rtlhal->current_bandtype == BAND_ON_2_4G)
		_rtl8822be_phy_set_txpower_level_by_path(
			hw, cck_rates, path, channel, sizes_of_cck_retes);
	_rtl8822be_phy_set_txpower_level_by_path(hw, ofdm_rates, path, channel,
						 sizes_of_ofdm_retes);
	_rtl8822be_phy_set_txpower_level_by_path(hw, ht_rates_1t, path, channel,
						 sizes_of_ht_retes_1t);
	_rtl8822be_phy_set_txpower_level_by_path(hw, ht_rates_2t, path, channel,
						 sizes_of_ht_retes_2t);
	_rtl8822be_phy_set_txpower_level_by_path(hw, vht_rates_1t, path,
						 channel, sizes_of_vht_retes);
	_rtl8822be_phy_set_txpower_level_by_path(hw, vht_rates_2t, path,
						 channel, sizes_of_vht_retes);
}