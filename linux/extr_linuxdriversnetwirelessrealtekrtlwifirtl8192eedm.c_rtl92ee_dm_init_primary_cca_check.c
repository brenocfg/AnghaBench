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
struct dynamic_primary_cca {scalar_t__ mf_state; scalar_t__ ch_offset; scalar_t__ monitor_flag; scalar_t__ intf_type; scalar_t__ intf_flag; scalar_t__ dup_rts_flag; } ;
struct rtl_priv {struct dynamic_primary_cca primarycca; } ;
struct rtl_hal {scalar_t__ rts_en; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92ee_dm_init_primary_cca_check(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	struct dynamic_primary_cca *primarycca = &rtlpriv->primarycca;

	rtlhal->rts_en = 0;
	primarycca->dup_rts_flag = 0;
	primarycca->intf_flag = 0;
	primarycca->intf_type = 0;
	primarycca->monitor_flag = 0;
	primarycca->ch_offset = 0;
	primarycca->mf_state = 0;
}