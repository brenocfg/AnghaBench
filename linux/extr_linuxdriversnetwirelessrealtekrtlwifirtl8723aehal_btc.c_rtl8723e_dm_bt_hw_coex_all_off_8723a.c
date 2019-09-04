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
 int /*<<< orphan*/  rtl8723e_dm_bt_set_coex_table (struct ieee80211_hw*,int,int,int) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_set_hw_pta_mode (struct ieee80211_hw*,int) ; 

void rtl8723e_dm_bt_hw_coex_all_off_8723a(struct ieee80211_hw *hw)
{
	rtl8723e_dm_bt_set_coex_table(hw, 0x5a5aaaaa, 0xcc, 0x3);
	rtl8723e_dm_bt_set_hw_pta_mode(hw, true);
}