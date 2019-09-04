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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl8812ae_phy_set_txpower_limit (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _rtl8812ae_phy_config_bb_txpwr_lmt(struct ieee80211_hw *hw,
					  u8 *regulation, u8 *band,
					  u8 *bandwidth, u8 *rate_section,
					  u8 *rf_path, u8 *channel,
					  u8 *power_limit)
{
	_rtl8812ae_phy_set_txpower_limit(hw, regulation, band, bandwidth,
					 rate_section, rf_path, channel,
					 power_limit);
}