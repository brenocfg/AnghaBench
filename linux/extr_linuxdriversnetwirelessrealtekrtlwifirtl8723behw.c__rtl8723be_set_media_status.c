#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {scalar_t__ link_state; } ;
struct rtl_priv {TYPE_3__* cfg; TYPE_1__ mac80211; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
typedef  enum led_ctl_mode { ____Placeholder_led_ctl_mode } led_ctl_mode ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* led_control ) (struct ieee80211_hw*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 int LED_CTL_LINK ; 
 int LED_CTL_NO_LINK ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ MSR ; 
 int MSR_ADHOC ; 
 int MSR_AP ; 
 int MSR_INFRA ; 
 int MSR_NOLINK ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_MESH_POINT 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_UNSPECIFIED 128 
 scalar_t__ REG_BCNTCFG ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _rtl8723be_disable_bcn_sub_func (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8723be_enable_bcn_sub_func (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8723be_resume_tx_beacon (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8723be_stop_tx_beacon (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int) ; 

__attribute__((used)) static int _rtl8723be_set_media_status(struct ieee80211_hw *hw,
				       enum nl80211_iftype type)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bt_msr = rtl_read_byte(rtlpriv, MSR) & 0xfc;
	enum led_ctl_mode ledaction = LED_CTL_NO_LINK;
	u8 mode = MSR_NOLINK;

	switch (type) {
	case NL80211_IFTYPE_UNSPECIFIED:
		mode = MSR_NOLINK;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "Set Network type to NO LINK!\n");
		break;
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_MESH_POINT:
		mode = MSR_ADHOC;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "Set Network type to Ad Hoc!\n");
		break;
	case NL80211_IFTYPE_STATION:
		mode = MSR_INFRA;
		ledaction = LED_CTL_LINK;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "Set Network type to STA!\n");
		break;
	case NL80211_IFTYPE_AP:
		mode = MSR_AP;
		ledaction = LED_CTL_LINK;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			 "Set Network type to AP!\n");
		break;
	default:
		pr_err("Network type %d not support!\n", type);
		return 1;
	}

	/* MSR_INFRA == Link in infrastructure network;
	 * MSR_ADHOC == Link in ad hoc network;
	 * Therefore, check link state is necessary.
	 *
	 * MSR_AP == AP mode; link state is not cared here.
	 */
	if (mode != MSR_AP && rtlpriv->mac80211.link_state < MAC80211_LINKED) {
		mode = MSR_NOLINK;
		ledaction = LED_CTL_NO_LINK;
	}

	if (mode == MSR_NOLINK || mode == MSR_INFRA) {
		_rtl8723be_stop_tx_beacon(hw);
		_rtl8723be_enable_bcn_sub_func(hw);
	} else if (mode == MSR_ADHOC || mode == MSR_AP) {
		_rtl8723be_resume_tx_beacon(hw);
		_rtl8723be_disable_bcn_sub_func(hw);
	} else {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 "Set HW_VAR_MEDIA_STATUS: No such media status(%x).\n",
			 mode);
	}

	rtl_write_byte(rtlpriv, MSR, bt_msr | mode);
	rtlpriv->cfg->ops->led_control(hw, ledaction);
	if (mode == MSR_AP)
		rtl_write_byte(rtlpriv, REG_BCNTCFG + 1, 0x00);
	else
		rtl_write_byte(rtlpriv, REG_BCNTCFG + 1, 0x66);
	return 0;
}