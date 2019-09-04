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
typedef  int u32 ;
struct rtl_phy {scalar_t__ current_chan_bw; scalar_t__ rf_type; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;

/* Variables and functions */
 int BIT21 ; 
 int BIT31 ; 
 scalar_t__ HT_CHANNEL_WIDTH_20_40 ; 
 scalar_t__ HT_CHANNEL_WIDTH_80 ; 
 scalar_t__ RF_1T1R ; 
 int WIRELESS_MODE_AC_24G ; 
 int WIRELESS_MODE_AC_5G ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u32 _rtl8821ae_set_ra_vht_ratr_bitmap(struct ieee80211_hw *hw,
					     enum wireless_mode wirelessmode,
					     u32 ratr_bitmap)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u32 ret_bitmap = ratr_bitmap;

	if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40
		|| rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80)
		ret_bitmap = ratr_bitmap;
	else if (wirelessmode == WIRELESS_MODE_AC_5G
		|| wirelessmode == WIRELESS_MODE_AC_24G) {
		if (rtlphy->rf_type == RF_1T1R)
			ret_bitmap = ratr_bitmap & (~BIT21);
		else
			ret_bitmap = ratr_bitmap & (~(BIT31|BIT21));
	}

	return ret_bitmap;
}