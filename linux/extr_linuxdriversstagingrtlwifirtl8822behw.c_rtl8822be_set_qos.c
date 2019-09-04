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
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;
struct rtl_mac {int /*<<< orphan*/ * edca_param; int /*<<< orphan*/  mode; int /*<<< orphan*/  vif; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
#define  AC0_BE 131 
#define  AC1_BK 130 
#define  AC2_VI 129 
#define  AC3_VO 128 
 int /*<<< orphan*/  REG_EDCA_BE_PARAM_8822B ; 
 int /*<<< orphan*/  REG_EDCA_BK_PARAM_8822B ; 
 int /*<<< orphan*/  REG_EDCA_VI_PARAM_8822B ; 
 int /*<<< orphan*/  REG_EDCA_VO_PARAM_8822B ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  rtl_get_hal_edca_param (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl8822be_set_qos(struct ieee80211_hw *hw, int aci)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtlpriv);
	u32 ac_param;

	ac_param = rtl_get_hal_edca_param(hw, mac->vif, mac->mode,
					  &mac->edca_param[aci]);

	switch (aci) {
	case AC1_BK:
		rtl_write_dword(rtlpriv, REG_EDCA_BK_PARAM_8822B, ac_param);
		break;
	case AC0_BE:
		rtl_write_dword(rtlpriv, REG_EDCA_BE_PARAM_8822B, ac_param);
		break;
	case AC2_VI:
		rtl_write_dword(rtlpriv, REG_EDCA_VI_PARAM_8822B, ac_param);
		break;
	case AC3_VO:
		rtl_write_dword(rtlpriv, REG_EDCA_VO_PARAM_8822B, ac_param);
		break;
	default:
		WARN_ONCE(true, "invalid aci: %d !\n", aci);
		break;
	}
}