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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ act_scanning; } ;
struct rtl_hal {int /*<<< orphan*/  version; int /*<<< orphan*/  current_bandtype; } ;
struct rtl_phy {int lck_inprogress; } ;
struct rtl_priv {TYPE_1__ mac80211; struct rtl_hal rtlhal; struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FINIT ; 
 int /*<<< orphan*/  INIT_IQK ; 
 scalar_t__ IS_92D_SINGLEPHY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _rtl92d_phy_lc_calibrate (struct ieee80211_hw*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl92d_phy_lc_calibrate(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u32 timeout = 2000, timecount = 0;

	while (rtlpriv->mac80211.act_scanning && timecount < timeout) {
		udelay(50);
		timecount += 50;
	}

	rtlphy->lck_inprogress = true;
	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"LCK:Start!!! currentband %x delay %d ms\n",
		rtlhal->current_bandtype, timecount);
	if (IS_92D_SINGLEPHY(rtlhal->version)) {
		_rtl92d_phy_lc_calibrate(hw, true);
	} else {
		/* For 1T1R */
		_rtl92d_phy_lc_calibrate(hw, false);
	}
	rtlphy->lck_inprogress = false;
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "LCK:Finish!!!\n");
}