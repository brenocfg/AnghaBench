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
struct rtl_sta_info {int dummy; } ;
struct rtl_priv {int dummy; } ;
struct phy_dm_struct {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_CMNINFO_STA_STATUS ; 
 int /*<<< orphan*/  _rtl_phydm_get_macid (struct rtl_priv*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  odm_cmn_info_ptr_array_hook (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtl_sta_info*) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_add_sta(struct rtl_priv *rtlpriv,
			      struct ieee80211_sta *sta)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);
	struct rtl_sta_info *sta_entry = (struct rtl_sta_info *)sta->drv_priv;
	u8 mac_id = _rtl_phydm_get_macid(rtlpriv, sta);

	odm_cmn_info_ptr_array_hook(dm, ODM_CMNINFO_STA_STATUS, mac_id,
				    sta_entry);

	return true;
}