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
typedef  int u8 ;
struct rtl_sta_info {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;

/* Variables and functions */

__attribute__((used)) static u8 _rtl8821ae_get_ra_ldpc(struct ieee80211_hw *hw,
			     u8 mac_id, struct rtl_sta_info *sta_entry,
			     enum wireless_mode wirelessmode)
{
	u8 b_ldpc = 0;
	/*not support ldpc, do not open*/
	return b_ldpc << 2;
}