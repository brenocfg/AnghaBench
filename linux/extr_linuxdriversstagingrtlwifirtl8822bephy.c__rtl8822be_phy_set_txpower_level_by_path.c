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
typedef  size_t u8 ;
struct rtl_phy {int /*<<< orphan*/  current_chan_bw; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {struct rtl_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl8822be_phy_set_txpower_index (struct ieee80211_hw*,size_t,size_t,size_t) ; 
 size_t rtl8822be_get_txpower_index (struct ieee80211_hw*,size_t,size_t,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8822be_phy_set_txpower_level_by_path(struct ieee80211_hw *hw,
						     u8 *array, u8 path,
						     u8 channel, u8 size)
{
	struct rtl_phy *rtlphy = &(rtl_priv(hw)->phy);
	u8 i;
	u8 power_index;

	for (i = 0; i < size; i++) {
		power_index = rtl8822be_get_txpower_index(
			hw, path, array[i], rtlphy->current_chan_bw, channel);
		_rtl8822be_phy_set_txpower_index(hw, power_index, path,
						 array[i]);
	}
}