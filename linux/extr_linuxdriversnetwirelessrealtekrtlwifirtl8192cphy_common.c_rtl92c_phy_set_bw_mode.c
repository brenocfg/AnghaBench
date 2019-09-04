#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rtl_phy {int set_bwmode_inprogress; int /*<<< orphan*/  current_chan_bw; } ;
struct rtl_priv {TYPE_2__* cfg; struct rtl_phy phy; } ;
struct rtl_hal {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* phy_set_bw_mode_callback ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 int /*<<< orphan*/  RT_CANNOT_IO (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_hal_stop (struct rtl_hal*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 

void rtl92c_phy_set_bw_mode(struct ieee80211_hw *hw,
			    enum nl80211_channel_type ch_type)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 tmp_bw = rtlphy->current_chan_bw;

	if (rtlphy->set_bwmode_inprogress)
		return;
	rtlphy->set_bwmode_inprogress = true;
	if ((!is_hal_stop(rtlhal)) && !(RT_CANNOT_IO(hw))) {
		rtlpriv->cfg->ops->phy_set_bw_mode_callback(hw);
	} else {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 "false driver sleep or unload\n");
		rtlphy->set_bwmode_inprogress = false;
		rtlphy->current_chan_bw = tmp_bw;
	}
}