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
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;
struct rtl_priv {TYPE_1__ mac80211; } ;
struct rtl_mac {scalar_t__ link_state; int /*<<< orphan*/  p2p; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr3; } ;

/* Variables and functions */
 int FCS_LEN ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  ether_addr_equal_64bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_action (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_p2p_action_ie (struct ieee80211_hw*,void*,unsigned int) ; 
 int /*<<< orphan*/  rtl_p2p_noa_ie (struct ieee80211_hw*,void*,unsigned int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl_p2p_info(struct ieee80211_hw *hw, void *data, unsigned int len)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct ieee80211_hdr *hdr = data;

	if (!mac->p2p)
		return;
	if (mac->link_state != MAC80211_LINKED)
		return;
	/* min. beacon length + FCS_LEN */
	if (len <= 40 + FCS_LEN)
		return;

	/* and only beacons from the associated BSSID, please */
	if (!ether_addr_equal_64bits(hdr->addr3, rtlpriv->mac80211.bssid))
		return;

	/* check if this really is a beacon */
	if (!(ieee80211_is_beacon(hdr->frame_control) ||
	      ieee80211_is_probe_resp(hdr->frame_control) ||
	      ieee80211_is_action(hdr->frame_control)))
		return;

	if (ieee80211_is_action(hdr->frame_control))
		rtl_p2p_action_ie(hw , data , len - FCS_LEN);
	else
		rtl_p2p_noa_ie(hw , data , len - FCS_LEN);
}