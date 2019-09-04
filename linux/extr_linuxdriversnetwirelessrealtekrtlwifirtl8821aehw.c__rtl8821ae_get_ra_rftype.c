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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rtl_phy {scalar_t__ rf_type; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;

/* Variables and functions */
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_2T2R ; 
 int WIRELESS_MODE_AC_24G ; 
 int WIRELESS_MODE_AC_5G ; 
 int WIRELESS_MODE_AC_ONLY ; 
 int WIRELESS_MODE_N_24G ; 
 int WIRELESS_MODE_N_5G ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u8 _rtl8821ae_get_ra_rftype(struct ieee80211_hw *hw,
			  enum wireless_mode wirelessmode,
			  u32 ratr_bitmap)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 rf_type = RF_1T1R;

	if (rtlphy->rf_type == RF_1T1R)
		rf_type = RF_1T1R;
	else if (wirelessmode == WIRELESS_MODE_AC_5G
		|| wirelessmode == WIRELESS_MODE_AC_24G
		|| wirelessmode == WIRELESS_MODE_AC_ONLY) {
		if (ratr_bitmap & 0xffc00000)
			rf_type = RF_2T2R;
	} else if (wirelessmode == WIRELESS_MODE_N_5G
		|| wirelessmode == WIRELESS_MODE_N_24G) {
		if (ratr_bitmap & 0xfff00000)
			rf_type = RF_2T2R;
	}

	return rf_type;
}