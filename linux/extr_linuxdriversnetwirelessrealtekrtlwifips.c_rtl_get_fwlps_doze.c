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
struct rtl_ps_ctl {scalar_t__ last_delaylps_stamp_jiffies; } ;
struct rtl_priv {int dummy; } ;
struct rtl_mac {scalar_t__ link_state; scalar_t__ opmode; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jiffies ; 
 int jiffies_to_msecs (scalar_t__) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_get_fwlps_doze(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	u32 ps_timediff;

	ps_timediff = jiffies_to_msecs(jiffies -
				       ppsc->last_delaylps_stamp_jiffies);

	if (ps_timediff < 2000) {
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "Delay enter Fw LPS for DHCP, ARP, or EAPOL exchanging state\n");
		return false;
	}

	if (mac->link_state != MAC80211_LINKED)
		return false;

	if (mac->opmode == NL80211_IFTYPE_ADHOC)
		return false;

	return true;
}