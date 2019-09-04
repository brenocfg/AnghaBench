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
struct dig_t {int /*<<< orphan*/  cursta_cstate; int /*<<< orphan*/  presta_cstate; } ;
struct rtl_priv {struct dig_t dm_digtable; } ;
struct rtl_mac {scalar_t__ link_state; scalar_t__ act_scanning; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIG_STA_CONNECT ; 
 int /*<<< orphan*/  DIG_STA_DISCONNECT ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  rtl8723e_dm_cck_packet_detection_thresh (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723e_dm_initial_gain_multi_sta (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723e_dm_initial_gain_sta (struct ieee80211_hw*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_ctrl_initgain_by_twoport(struct ieee80211_hw *hw)
{
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;

	if (mac->act_scanning)
		return;

	if (mac->link_state >= MAC80211_LINKED)
		dm_digtable->cursta_cstate = DIG_STA_CONNECT;
	else
		dm_digtable->cursta_cstate = DIG_STA_DISCONNECT;

	rtl8723e_dm_initial_gain_sta(hw);
	rtl8723e_dm_initial_gain_multi_sta(hw);
	rtl8723e_dm_cck_packet_detection_thresh(hw);

	dm_digtable->presta_cstate = dm_digtable->cursta_cstate;

}