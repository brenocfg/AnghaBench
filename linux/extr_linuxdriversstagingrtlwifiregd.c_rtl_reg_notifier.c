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
struct wiphy {int dummy; } ;
struct rtl_priv {int /*<<< orphan*/  regd; } ;
struct regulatory_request {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_REGD ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _rtl_reg_notifier_apply (struct wiphy*,struct regulatory_request*,int /*<<< orphan*/ *) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct ieee80211_hw* wiphy_to_ieee80211_hw (struct wiphy*) ; 

void rtl_reg_notifier(struct wiphy *wiphy, struct regulatory_request *request)
{
	struct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	RT_TRACE(rtlpriv, COMP_REGD, DBG_LOUD, "\n");

	_rtl_reg_notifier_apply(wiphy, request, &rtlpriv->regd);
}