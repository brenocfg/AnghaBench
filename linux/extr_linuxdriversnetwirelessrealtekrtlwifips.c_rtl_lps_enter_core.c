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
struct rtl_ps_ctl {int /*<<< orphan*/  fwctrl_lps; } ;
struct TYPE_5__ {int /*<<< orphan*/  lps_mutex; } ;
struct TYPE_4__ {scalar_t__ busytraffic; } ;
struct TYPE_6__ {scalar_t__ being_setkey; } ;
struct rtl_priv {TYPE_2__ locks; TYPE_1__ link_info; TYPE_3__ sec; } ;
struct rtl_mac {int cnt_after_linked; scalar_t__ opmode; scalar_t__ link_state; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  EAUTOPS ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl_lps_set_psmode (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 

__attribute__((used)) static void rtl_lps_enter_core(struct ieee80211_hw *hw)
{
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (!ppsc->fwctrl_lps)
		return;

	if (rtlpriv->sec.being_setkey)
		return;

	if (rtlpriv->link_info.busytraffic)
		return;

	/*sleep after linked 10s, to let DHCP and 4-way handshake ok enough!! */
	if (mac->cnt_after_linked < 5)
		return;

	if (mac->opmode == NL80211_IFTYPE_ADHOC)
		return;

	if (mac->link_state != MAC80211_LINKED)
		return;

	mutex_lock(&rtlpriv->locks.lps_mutex);

	/* Don't need to check (ppsc->dot11_psmode == EACTIVE), because
	 * bt_ccoexist may ask to enter lps.
	 * In normal case, this constraint move to rtl_lps_set_psmode().
	 */
	RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
		 "Enter 802.11 power save mode...\n");
	rtl_lps_set_psmode(hw, EAUTOPS);

	mutex_unlock(&rtlpriv->locks.lps_mutex);
}