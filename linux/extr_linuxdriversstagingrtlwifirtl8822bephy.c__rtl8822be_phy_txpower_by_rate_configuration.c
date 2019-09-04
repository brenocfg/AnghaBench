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
 int /*<<< orphan*/  _rtl8822be_phy_convert_txpower_dbm_to_relative_value (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8822be_phy_store_txpower_by_rate_base (struct ieee80211_hw*) ; 

__attribute__((used)) static void
_rtl8822be_phy_txpower_by_rate_configuration(struct ieee80211_hw *hw)
{
	/* copy rate_section from
	 * tx_power_by_rate_offset[][rate] to txpwr_by_rate_base_24g/_5g[][rs]
	 */
	_rtl8822be_phy_store_txpower_by_rate_base(hw);

	/* convert tx_power_by_rate_offset[] to relative value */
	_rtl8822be_phy_convert_txpower_dbm_to_relative_value(hw);
}