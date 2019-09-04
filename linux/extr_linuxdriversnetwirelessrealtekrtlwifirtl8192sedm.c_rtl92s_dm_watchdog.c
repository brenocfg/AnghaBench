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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl92s_dm_check_edca_turbo (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92s_dm_check_txpowertracking_thermalmeter (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92s_dm_ctrl_initgain_byrssi (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92s_dm_dynamic_txpower (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92s_dm_refresh_rateadaptive_mask (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92s_dm_switch_baseband_mrc (struct ieee80211_hw*) ; 

void rtl92s_dm_watchdog(struct ieee80211_hw *hw)
{
	_rtl92s_dm_check_edca_turbo(hw);
	_rtl92s_dm_check_txpowertracking_thermalmeter(hw);
	_rtl92s_dm_ctrl_initgain_byrssi(hw);
	_rtl92s_dm_dynamic_txpower(hw);
	_rtl92s_dm_refresh_rateadaptive_mask(hw);
	_rtl92s_dm_switch_baseband_mrc(hw);
}